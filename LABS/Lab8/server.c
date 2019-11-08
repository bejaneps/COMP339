#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/sendfile.h>
#include <stdlib.h>

int main()
{    
		int sock_fd, new_socket, ret;
		struct sockaddr_in address;
		int addrlen = sizeof(address);
		char buffer[2048] = {0}; // to read a message from a client to a buffer
		int new_file; // to create a new file and copy content of recv file to newfile
		int file_len = 0; // length of the newfile received

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
		address.sin_port=htons(6666);
		 
		if(bind(sock_fd,(struct sockaddr*)&address,sizeof(address))<0){
			printf("\n error, Binding went wrong");
			return-1;
		}
		
		if(listen(sock_fd,4)<0){
			printf("\n error, Listening part is not working");
			return-1;
		}
		
		if((new_socket=accept(sock_fd,(struct sockaddr*)&address,(socklen_t*)&addrlen))<0){
			printf("\n error, Accepting part is not working");
    		return-1;
    	}
    	
    	new_file = creat("client_file.txt", 0666);
		if(new_file == -1){
			perror("\n creat");
			return -1;
		}
		
		ret = recv(new_socket, buffer, 2048, 0);
		if(ret == -1){
			perror("\n read");
			return -1;
		}
		file_len = atoi(buffer);
		
		ret = sendfile(new_file, new_socket, NULL, file_len);
		if(ret == -1){
			perror("\n sendfile");
			return -1;
		}
		
		/*
		ret = recv(new_socket, buffer, 2048, 0);
		if(ret == -1){
			perror("\n receive");
			return -1;
		}	
		
		ret = write(new_file, buffer, strlen(buffer));
		if(ret == -1){
			perror("\n write");
			return -1;
		}
		*/
		
		fprintf(stdout, "File client_file.txt created and contents copied.\n");
		
		close(sock_fd);
		close(new_file);
		
		return 0;
}

