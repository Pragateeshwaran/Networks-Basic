#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h> // used for sockaddr_in, INADDR_ANY
#include<arpa/inet.h> // used for htons, htonl
#include<sys/socket.h> // used for AF_INET, SOCK_STREAM, socket(), bind(), listen(), accept(), connect()
#include<unistd.h> // used for read(), write(), close()
#include<string.h>
#define PORT 8999
#define MAX_LEN 128

int function(int conn) {
    char buff[MAX_LEN];
    int n = 0;

    for (;;) {
        // Get user input to send to the server
        bzero(buff, MAX_LEN);  // Clear the buffer before taking new input
        printf("Enter message: ");
        while ((buff[n++] = getchar()) != '\n') {}

        // Send the message to the server
        write(conn, buff, strlen(buff));  // Send the message

        // Read server response
        int bytesRead = read(conn, buff, sizeof(buff));
        if (bytesRead <= 0) {
            printf("Error or server disconnected (bytesRead = %d).\n", bytesRead);
            break;
        }
        buff[bytesRead] = '\0'; // Ensure null termination of the received message
        printf("Server:\t%s\n", buff);

        // Exit condition
        if (strncmp("exit", buff, 4) == 0) {
            break;
        }
    }
    return 1;
}

int main() {
    struct sockaddr_in client;
    int sockfd;

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("Error Socket creation\n");
        exit(0);
    } else {
        printf("Socket Created successfully.\n");
    }

    client.sin_family = AF_INET; // address family (IPv4)
    client.sin_addr.s_addr = inet_addr("127.0.0.1"); // Localhost
    client.sin_port = htons(PORT); // Port number

    // Connect to server
    if (connect(sockfd, (struct sockaddr*)&client, sizeof(client)) != 0) {
        printf("Error connecting to server\n");
        exit(0);
    }

    printf("Connecting to Server...\n");

    // Start communication with the server
    function(sockfd);

    // Close the socket
    close(sockfd);

    return 0;
}

