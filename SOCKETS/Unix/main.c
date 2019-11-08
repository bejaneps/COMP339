/*

This is a complete UNIX socket echo server. It uses signals for graceful exit and handling of children, fork to handle multiple clients at the same time. The instructions on how to connect to the server is given when you run the program.

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>
#include <wait.h>
#include <sys/un.h>

//server socket
int server;

#define SOCKETFILE "sock.temp"

//handles sigint, sigchld, sigterm
void handler(int sig) {
    //in case of interrupt or term, exit gracefully
    if(sig == SIGINT || sig == SIGTERM) {
        printf("Exiting on request.\n");
        //close server socket
        close(server);
        //remove socket file
        unlink("sock.temp");
        //exit
        exit(0);
    }
    else if(sig == SIGCHLD) {
        //cull the child
        wait(NULL);
    }
}

//this function will be perform echo operation until the remote
//socket is closed
void echoop(int sock) {
    char buf[1024];
    int size;
    while((size = recv(sock, buf, 1024, 0)) > 0)
        send(sock, buf, size, 0);
}

int main() {
    //Display usage. \e[...m is used for bold/italic/color
    printf("\e[1mUnix Socket Echo server\e[0m\n");
    
    printf("You may use \e[3m\e[31msocat - UNIX-CONNECT:/sock.temp\e[0m"
           "to connect to this server on a separate terminal.\n");
    
    printf("While you are connected, issue \e[3m\e[31mpgrep 7-unix\e[0m to see the children.\n"
           "Use Ctrl+C on socat to disconnect, check pgrep again.\n");
    
    printf("Use Ctrl+C or \e[3m\e[31mkillall 7-unix\e[0m to terminate this application.\n");
    
    //bind signals
    signal(SIGINT, &handler);
    signal(SIGCHLD, &handler);
    signal(SIGTERM, &handler);
    
    //create server socket
    server = socket(AF_UNIX, SOCK_STREAM, 0);
    
    if(server == -1) {
        perror("Socket");
        return -1;
    }
    
    int result;
    
    //create server address struct
    struct sockaddr_un local;
    
    local.sun_family = AF_UNIX;
    strcpy(local.sun_path, SOCKETFILE);
    
    //bind the socket to the given file
    result = bind(server, (struct sockaddr*)&local, sizeof(local));
    
    if(result == -1) {
        perror("Bind");
        return -2; 
    }
    
    //start listening for connections
    result = listen(server, 5);
    
    if(result == -1) {
        perror("Listen");
        return -3;
    }
    
    //start accept loop
    while(1) {
        struct sockaddr_un remote;
        int len = sizeof(remote);
        
        //wait and accept for a new connection
        int newsock = accept(server, (struct sockaddr*)&remote, &len);
        
        //instead of exiting on error, retry after a second
        if(newsock == -1) {
            perror("Accept");
            printf("Retrying in 1 second\n");
            sleep(1);
            continue;
        }
        
        int pid = fork();
        
        //in case of an error we don't actually need to quit
        //simply do not use a new process, perform operation
        //in serial
        if(pid == -1) {
            //do not close any sockets, we need them all
            echoop(newsock);
            
            //we are done with this
            close(newsock);
            
            //dont exit, we will continue to be a server
        }
        else if(pid == 0) {
            //we don't need server socket
            close(server);
            
            //perform echo operation
            echoop(newsock);
            
            //we are done
            close(newsock);
            exit(0);
        }
        else {
            //child will handle this
            close(newsock);
        }
    }
}