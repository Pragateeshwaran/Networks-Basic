#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<netinet/in.h> // used for sockadd_in struct, INADDR_ANY
#include<sys/socket.h> // used for AF_INET, SOCK_STREAM, socket()
#include<unistd.h> // used for read(), write(), close() 
#include<arpa/inet.h> // used for htons, htonl
#define PORT 8080
#define MAX_LEN 128

int function(int conn){
	char buff[MAX_LEN];
	for(;;){
		
		read(conn, buff, sizeof(buff));
		printf("Client:\t%s}", buff);
		
		bzero(buff, MAX_LEN);
		int n = 0;
		
		while(buff[n++] = getchar() != '\n'){
		}
		
		write(conn, buff, sizeof(buff));
		
		if(strncmp("exit", buff, 4) == 0){
			return 1;
		}

	}

}

int main(){
	int i, j;
	struct sockaddr_in server, client;
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1){
		printf("Error Socket creation\n");
		exit(0);
	}
	else
		printf("Socket Created successfully.\n");

	server.sin_family = AF_INET; // address family - here represents IPv4 for IPv6 AF_INET6 is used
	server.sin_addr.s_addr = htonl(INADDR_ANY);  //INADDR_ANY - internet address allow anything, htonl() - Host-to-Network Long
	server.sin_port = htons(PORT); // htons() - (Host-to-Network Short)	
	
	if((bind(sockfd, (struct sockaddr* ) &server, sizeof(server)))!= 0){
		printf("Not Binded successfully.\n");
		exit(0);
	}
	else{
		printf("BINDED SUCCESSFULLY.\n");
	}

	if((listen(sockfd, 5)) != 0){
		printf("Listen failed");
		exit(0);
	}
	else{
		printf("Listening...\n");
	}

	int len = sizeof(client);
	
	int conn = accept(sockfd, (struct sockaddr*) &client, &len);
	if(conn < 0){
		printf("ERROR in CONN.\n");
		exit(0);
	}

	function(conn);
	close(sockfd);
}













