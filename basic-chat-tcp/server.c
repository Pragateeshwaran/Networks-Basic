#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h> // used for sockaddr_in, INADDR_ANY
#include<sys/socket.h> // used for AF_INET, SOCK_STREAM, socket(), bind(), listen(), accept()
#include<unistd.h> // used for read(), write(), close()
#include<arpa/inet.h> // used for htons, htonl
#include<string.h>
#define PORT 8999
#define MAX_LEN 128

int function(int conn) {
    char buff[MAX_LEN];
    int n = 0;

    for (;;) {
        // Read message from client
        int bytesRead = read(conn, buff, sizeof(buff));
        if (bytesRead <= 0) {
            printf("Error or client disconnected (bytesRead = %d).\n", bytesRead);
            break;
        }
        buff[bytesRead] = '\0'; // Ensure null termination of the received message
        printf("Client:\t%s\n", buff);

        // Get input from server to send back to the client
        n = 0;
        bzero(buff, MAX_LEN);  // Clear the buffer before taking new input
        while ((buff[n++] = getchar()) != '\n') {}

        // Debugging print to check what we are sending back
        printf("Server Sending:\t%s\n", buff);

        // Send the message back to the client
        write(conn, buff, strlen(buff));  // Use strlen(buff) instead of sizeof(buff)

        // Exit condition
        if (strncmp("exit", buff, 4) == 0) {
            break;
        }
    }
    return 1;
}

int main() {
    struct sockaddr_in server, client;
    int len, sockfd;

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("Error Socket creation\n");
        exit(0);
    } else {
        printf("Socket Created successfully.\n");
    }

    server.sin_family = AF_INET; // address family - here represents IPv4
    server.sin_addr.s_addr = htonl(INADDR_ANY);  // INADDR_ANY - accept connections from any address
    server.sin_port = htons(PORT); // Port number

    // Bind the server socket
    if (bind(sockfd, (struct sockaddr*)&server, sizeof(server)) != 0) {
        printf("Not Binded successfully.\n");
        exit(0);
    } else {
        printf("BINDED SUCCESSFULLY.\n");
    }

    // Listen for incoming connections
    if (listen(sockfd, 5) != 0) {
        printf("Listen failed\n");
        exit(0);
    } else {
        printf("Listening...\n");
    }

    len = sizeof(client);

    // Accept client connection
    int conn = accept(sockfd, (struct sockaddr*)&client, &len);
    if (conn < 0) {
        printf("ERROR in CONNECTION.\n");
        exit(0);
    }

    // Call function to handle communication
    function(conn);

    // Close the connection
    close(sockfd);
    return 0;
}
