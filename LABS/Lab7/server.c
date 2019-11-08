#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int main()
{    //1.CREATE SOCKET
   	int sock_fd,new_socket,valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[2048]={0};
    char *message="  Hi";
    
    ////domain=AF_INET for  internet domain, domain = AF_UNIX for unix
    ///communication type = STREAM for TCP and DATAGRAM for UDP
    ///0 = protocol or refering to IP, if the socket is nit working, it will return a negative number

    if((sock_fd=socket(AF_INET,SOCK_STREAM,0))<0)
    {
 
    printf("\n error, Socket is not working \n");
    return-1;
    }
    ///Address family is set as internet
    address.sin_family=AF_INET;
    ///seting an IP address
    address.sin_addr.s_addr=INADDR_ANY;
    ///setting port number
    address.sin_port=htons(5555);
     
    ///the socket file descriptor returned by socket = sock_fd
    ///a pointer to sockaddr the hold information for IP and port
    ///size of address
    if(bind(sock_fd,(struct sockaddr*)&address,sizeof(address))<0){
    printf("\n error, Binding went wrong");
    return-1;
    }
    
    ///the socket file descriptor returned by socket = sock_fd
    ///number of connections allowed in the queue
    if(listen(sock_fd,4)<0){
    printf("\n error, Listening part is not working");
    return-1;
    }
    
    if((new_socket=accept(sock_fd,(struct sockaddr*)&address,(socklen_t*)&addrlen))<0){
    printf("\n error, Accepting part is not working");
    return-1;
    }
    
    valread=recv(new_socket,buffer,2048,0);
    printf("%s\n",buffer);
    send(new_socket,message,strlen(message),0);
    printf("Message Recieved\n");
    return 0;
}
