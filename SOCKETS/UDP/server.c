#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(){
	int udpSocket, nBytes;
	char buffer[1024];
	struct sockaddr_in serverAddr, clientAddr;
	struct sockaddr_storage serverStorage;
	socklen_t addr_size, client_addr_size;
	int i;

	/*Create UDP socket*/
	udpSocket = socket(PF_INET, SOCK_DGRAM, 0);

	/*Configure settings in address struct*/
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(7891);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

	/*Bind socket with address struct*/
	bind(udpSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

	/*Initialize size variable to be used later on*/
	addr_size = sizeof serverStorage;

	while(1)
	{
		printf("Type a sentence to send to client:\n");
		fgets(buffer,1024,stdin);
		printf("You typed: %s",buffer);

		nBytes = strlen(buffer) + 1;

		sendto(udpSocket,buffer,nBytes,0,(struct sockaddr *)&serverStorage,addr_size);

		/* Try to receive any incoming UDP datagram. Address and port of 
			requesting client will be stored on serverStorage variable */
		nBytes = recvfrom(udpSocket,buffer,1024,0,(struct sockaddr *)&serverStorage, &addr_size);

		printf("Received from client: %s\n",buffer);
	}

	return 0;
}
