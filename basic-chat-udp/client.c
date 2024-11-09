#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<sys/socket.h>
#define PORT 8999
#define MAX_LEN 128

int forward(int sockfd, struct sockaddr_in server){
	
	char buff[MAX_LEN];
	int n = 0;

	for(;;){
	
		printf("Enter Message: ");
		while((buff[n++] = getchar()) != '\n'){}

		sendto(sockfd, buff, strlen(buff), 0, (struct sockaddr*) &server, sizeof(server));

		int len = sizeof(server);
		int byte = recvfrom(sockfd, buff, sizeof(buff), 0, (struct sockaddr*)&server, &len);
		if(byte <= 0){
			printf("error byte");
			break;
		}
		buff[byte] = '\0';
		printf("server:\t%s\n", buff);

		if (strncmp("exit", buff, 4) == 0){
			break;
		}
	}
	return 1;
}


int main(){
	int sockfd;
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd == -1){
		printf("ERROR at socket");
		exit(0);
	}
	else{
		printf("socket created.\n");
	}

	struct sockaddr_in server;

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_port = htons(PORT);

	forward(sockfd, server);
	close(sockfd);
}
