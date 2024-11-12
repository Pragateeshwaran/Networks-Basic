#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>

// Function to get local machine information
void get_local_info() {
    char hostname[256];
    struct hostent *host_entry;

    // Get the hostname of the local machine
    if (gethostname(hostname, sizeof(hostname)) != 0) {
        perror("gethostname");
        return;
    }

    // Get host entry based on hostname
    host_entry = gethostbyname(hostname);
    if (host_entry == NULL) {
        perror("gethostbyname");
        return;
    }

    printf("Local Hostname: %s\n", hostname);
    printf("Local IP Address: %s\n", inet_ntoa(*(struct in_addr *)host_entry->h_addr_list[0]));
}

// Function to perform forward DNS lookup
void forward_dns_lookup(const char *domain) {
    struct hostent *host_entry = gethostbyname(domain);
    if (host_entry == NULL) {
        perror("gethostbyname");
        return;
    }

    printf("Domain: %s\n", domain);
    for (int i = 0; host_entry->h_addr_list[i] != NULL; i++) {
        printf("IP Address: %s\n", inet_ntoa(*(struct in_addr *)host_entry->h_addr_list[i]));
    }
}

// Function to perform reverse DNS lookup
void reverse_dns_lookup(const char *ip_address) {
    struct in_addr addr;
    struct hostent *host_entry;

    // Convert IP address from string to binary form
    if (inet_aton(ip_address, &addr) == 0) {
        fprintf(stderr, "Invalid IP address format.\n");
        return;
    }

    // Get host entry based on IP address
    host_entry = gethostbyaddr(&addr, sizeof(addr), AF_INET);
    if (host_entry == NULL) {
        perror("gethostbyaddr");
        return;
    }

    printf("IP Address: %s\n", ip_address);
    printf("Hostname: %s\n", host_entry->h_name);
}

int main() {
    int choice;
    char domain[256];
    char ip_address[16];

    while (1) {
        printf("\nDNS Lookup Menu:\n");
        printf("1. Get Local Information\n");
        printf("2. Forward DNS Lookup\n");
        printf("3. Reverse DNS Lookup\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            fprintf(stderr, "Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); // Clear invalid input
            continue;
        }

        switch (choice) {
            case 1:
                get_local_info();
                break;
            case 2:
                printf("Enter domain name: ");
                scanf("%s", domain);
                forward_dns_lookup(domain);
                break;
            case 3:
                printf("Enter IP address: ");
                scanf("%s", ip_address);
                reverse_dns_lookup(ip_address);
                break;
            case 4:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
