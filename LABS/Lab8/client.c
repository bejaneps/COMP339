#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/sendfile.h>

int main()
{
        struct sockaddr_in address, serv_addr;
        struct stat file_info; // for opened file info
        int sock=0, newfile, ret;
        char buffer[2048] = {0}; // to write the file content into buffer
        
        if((sock=socket(AF_INET,SOCK_STREAM,0))<0){
	 		perror("\n error, Socket is not working\n");
		    return -1;
        }
    
        memset(&serv_addr,'0',sizeof(serv_addr));
        
        serv_addr.sin_family=AF_INET;
        serv_addr.sin_port=htons(6666);


        if(inet_pton(AF_INET,"127.0.0.1",&serv_addr.sin_addr)<=0){
		    perror("\n invalid Address\n");
		    return -1;
        }
        
        if(connect(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0){
		    perror("\nNo connection");
		    return -1;
        }
        
        newfile = open("server_file.txt", O_RDONLY, 0666);
        if(newfile == -1){
        	perror("\nopen");
        	return -1;
        }
        fstat(newfile, &file_info);
        sprintf(buffer, "%ld", file_info.st_size);
        
        ret = send(sock, buffer, strlen(buffer), 0);
        if(ret == -1){
        	perror("\n send");
        	return -1;
        }
        
        ret = sendfile(sock, newfile, NULL, file_info.st_size);
        if(ret == -1){
        	perror("\n sendfile");
        	return -1;
        }
        
        fprintf(stdout, "File sent\n");
        
        /*
        ret = read(newfile, buffer, file_info.st_size);
        if(ret == -1){
        	perror("\n file read to buf");
        	return -1;
        }
        
        ret = send(sock, buffer, strlen(buffer), 0);
        if(ret == -1){
        	perror("\n send");
        	return -1;
        }
        
        fprintf(stdout, "Message sent\n");
        */
        
        close(sock);
        close(newfile);
        
        return 0;
}
