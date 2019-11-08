/*

TCP client to send data to server.

*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

int main(int argv, char* argc[]) {
    
    //check parameters
    if(argv != 3) {
        printf("Usage: %s {host} {portnumber}\n", argc[0]);
        return 1;
    }
    
    //convert port string to number
    int port = atoi(argc[2]);
    
    //check port
    if(port <= 0) {
        printf("Invalid port number.\n");
    }
    
    //port and address is given from arguments
    struct sockaddr_in serv = {AF_INET, htons(port)};
    inet_pton(AF_INET, argc[1], &serv);
    
    //create socket
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    
    if(sock < 0) {
        perror("Socket error");
        
        return -1;
    }
    
    //make connection
    int result = connect(sock, (struct sockaddr*)&serv, sizeof(serv));
    
    if(result < 0) {
        printf("Cannot connect to %s:%s\n", argc[1], argc[2]);
        return 2;
    }
    
    //get data from user
    char chr[100], c;
    printf("Enter string to be sent to the server: ");
    for(int i = 0; (c = getchar()) != '\n'; i++)
    {
        chr[i] = c;
    }
    
    //send to server
    result = send(sock, chr, strlen(chr), 0);
    
    if(result < 0) {
        perror("Send error");
        
        return -1;
    }
    
    //get a reply
    char buf[1024];
    int len = recv(sock, buf, 1024, 0);
    
    if(len < 0) {
        perror("Receive error");
        
        return -1;
    }
    if(len == 0) {
        printf("Server did not sent any data\n");
    }
    else {
        //make c string
        buf[len] = 0;
        
        //show reply on screen
        printf("Data received:\n%s\n", buf);
    }
    
    close(sock);
    
    return 0;
}