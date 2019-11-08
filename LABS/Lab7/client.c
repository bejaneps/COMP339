#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>


int main()
{
	struct sockaddr_in address;
	int sock=0,valread;
	struct sockaddr_in serv_addr;
	char *message="Here I am client";
	char buffer[2048]={0};

	if((sock=socket(AF_INET,SOCK_STREAM,0))<0){
	////domain=AF_INET for  internet domain, domain = AF_UNIX for unix
	///communication type = STREAM for TCP and DATAGRAM for UDP
	///0 = protocol or refering to IP, if the socket is nit working, it will return a negative number
	printf("\n error, Socket is not working\n");
	return-1;
	}

	/// fill a block of memory with a particular value.
	memset(&serv_addr,'0',sizeof(serv_addr));

	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(5555);


	if(inet_pton(AF_INET,"127.0.0.1",&serv_addr.sin_addr)<=0){
	printf("\n invalid Address\n");
	return -1;
	}

	if(connect(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0){
	printf("\nNo connection");
	return -1;
	}
	
	send(sock,message, strlen(message),0);
	printf("\nMessage sent");
	valread=recv(sock,buffer,2048,0);
	printf("%s\n",buffer);
	return 0;

}
