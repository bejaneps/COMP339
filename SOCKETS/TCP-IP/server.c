/*

This program is a TCP echo server, sending back the data recieved.

*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdlib.h>
#include <wait.h>

int sock;
#define PORTNUM 6666


//CTRL+C handler
void intsig(int sig) {
    close(sock);
    printf("Exiting on request\n");
    exit(0);
}

//Is called when a child ends, we dont want them to stay as zombies
void chldsig(int sig) {
    int status;
    
    wait(&status);
    
    if(WEXITSTATUS(status) == 0)
        printf("Client is served.\n");
    else
        printf("Something went wrong while serving the client.\n");
}

int main() {
 
    //create new socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    
    if(sock < 0) {
        perror("Socket creation");
        exit(-1);
    }
    
    //to close the socket and exit on CTRL + C
    signal(SIGINT, &intsig);
    
    //whenever a child process terminates, simply kill them
    signal(SIGCHLD, &chldsig);
    
    //address for the server and address variable for client
    struct sockaddr_in serv = {AF_INET, htons(PORTNUM), INADDR_ANY}, cli;
    
    //size of the address structure
    int addrsize = sizeof(cli);
    
    int result;
    
    //bind to the port
    result = bind(sock, (struct sockaddr*)&serv, addrsize);

    if(result < 0) {
        perror("Bind error");
        close(sock); //we dont want to leave sockets open
        exit(-1);
    }
    
    //start listening. after this step, clients can request for connect
    result = listen(sock, 5);

    if(result < 0) {
        perror("Listen error");
        close(sock);
        exit(-1);
    }
    
    printf("Server is ready to accept connections.\n");
    
    //continuously accept connections. program can be stopped with CTRL+C, SIGINT
    while(1) {
        //accept a new connection, if there is no connection waiting to be accepted
        //this call will block
        int newsock = accept(sock, (struct sockaddr*)&cli, &addrsize);
        
        if(newsock < 0) {
            perror("Accept error");
            close(sock);
            exit(-1);
        }
        
        //create new process for the client
        int pid = fork();
        
        if(pid < 0) {
            perror("Fork error");
            close(sock);
            exit(-1);
        }

        if(pid == 0) {
            //new process do not need original socket, which is inherited
            //like the new socket
            close(sock);
            
            printf("Client is now being served.\n");
            
            //buffer to receive data
            char buf[1024];
            int size;
            
            //recv data from the client, if no data is present, this call will block
            while( (size = recv(newsock, buf, 1024, 0)) > 0 ) {
                //send the same data back to the sender
                result = send(newsock, buf, size, 0);
                
                //probably client quit right after sending data
                if(result < 0) {
                    perror("Send error");
                    close(newsock);
                    exit(-1);
                }
            }
            
            //size < 0 means that there is an error while calling recv
            if(size < 0) {
                perror("Recv error");
                close(newsock);
                exit(-1);
            }
            
            //size = 0 means connection closed, we are done in here
            close(newsock);
            
            //no problems at all.
            exit(0);
        }
        
        //close the unused socket, it will be used by the child process
        close(newsock);
    }
    
    return 0;
}