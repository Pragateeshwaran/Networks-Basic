#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <net/if.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/ethernet.h>
#include <net/if_arp.h>

int get_mac_address(const char *ip_address, unsigned char *mac_address) {
    int sock;
    struct arpreq arp_request;
    struct sockaddr_in *sin;

    // Create a socket
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("socket");
        return -1;
    }

    memset(&arp_request, 0, sizeof(arp_request));
    sin = (struct sockaddr_in *)&arp_request.arp_pa;
    sin->sin_family = AF_INET;
    
    // Convert the IP address to binary form
    if (inet_pton(AF_INET, ip_address, &sin->sin_addr) != 1) {
        perror("inet_pton");
        close(sock);
        return -1;
    }

    // Send the ARP request to get the MAC address
    if (ioctl(sock, SIOCGARP, &arp_request) < 0) {
        perror("ioctl");
        close(sock);
        return -1;
    }

    // Copy the MAC address from the ARP request
    memcpy(mac_address, arp_request.arp_ha.sa_data, ETHER_ADDR_LEN);
    close(sock);
    return 0;
}

int main() {
    unsigned char mac_address[ETHER_ADDR_LEN];
    char ip_address[32];

    printf("Enter the IP address: ");
    if (fgets(ip_address, sizeof(ip_address), stdin) == NULL) {
        printf("Error reading IP address.\n");
        return 1;
    }

    // Remove the newline character from the input
    ip_address[strcspn(ip_address, "\n")] = '\0';

    // Get the MAC address for the IP address
    if (get_mac_address(ip_address, mac_address) == 0) {
        printf("MAC address for %s: %02X:%02X:%02X:%02X:%02X:%02X\n",
               ip_address,
               mac_address[0], mac_address[1], mac_address[2],
               mac_address[3], mac_address[4], mac_address[5]);
    } else {
        printf("Failed to get MAC address.\n");
    }

    return 0;
}
