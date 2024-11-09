#include<netinet/in.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<string.h>
#include<unistd.h>
#define PORT 8999
#define MAX_LEN 128

int forward(int sockfd){
	int n;
	char buff[MAX_LEN];
	struct sockaddr_in client;
	int len = sizeof(client);

	for (;;){

		int byte = recvfrom(sockfd, buff, sizeof(buff), 0, (struct sockaddr*)&client, &len); 
		if(byte <= 0){
			printf("error at receive.\n");
			return 0;
		}
		buff[byte] = '\n';
		printf("the client:\t%s", buff);

		bzero(buff, MAX_LEN);
		printf("enter the message:\t");

		n = 0;
		while((buff[n++] = getchar()) !='\n'){}

		sendto(sockfd, buff, sizeof(buff), 0, (struct sockaddr*) &client, len);

		if(strncmp("exit", buff, 4) == 0){
			break;
		}
	}
}

		


int main(){

	int sockfd, len;
	struct sockaddr_in server;

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd == -1){
		printf("error in socket creation.\n");
		exit(0);
	}
	else{
		printf("socket created successfully.\n");
	}
	
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_port = htons(PORT);

	if(bind(sockfd, (struct sockaddr*) &server, sizeof(server)) != 0){
		printf("ERROR in bind.\n");
		exit(0);
	}
	else{
		printf("Bind successfully.\n");
	}

	forward(sockfd);
	close(sockfd);

}
