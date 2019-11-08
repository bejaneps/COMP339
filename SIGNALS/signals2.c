#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <wait.h>

//whether the child is working
int working = 0;

void sig(int signal) {
    if(signal == SIGINT) {
        printf("OK I am working now\n");
        working = 1;
    }
    else if(signal == SIGCHLD) {
        int status;
        
        wait(&status);
        
        if(WIFEXITED(status))
            printf("Child finished with status %d\n", WEXITSTATUS(status));
        else
            printf("Child crashed.\n");
    }
}

void dochild() {
    int enjoyed = 0;

    signal(SIGINT, &sig);
    
    while(!working) {
        printf("I'm enjoying the sun\n");
        enjoyed++; //count the number of times child enjoyed the sun
        sleep(1);
    }
    
    exit(enjoyed);
}

int main() {
    
    int pid = fork();
    
    if(pid == -1) {
        perror("Fork");
        return -1;
    }
    
    if(pid == 0) {
        dochild();
    }

    signal(SIGCHLD, &sig);
    
    while(1) {
        int opt;
        
        printf("Action (1- interrupt child, 2- term child, 3- exit): ");
        
        scanf("%d", &opt);
        
        switch(opt) {
        case 1:
            //send interrupt signal
            kill(pid, SIGINT);
            break;
        case 2:
            //send kill signal
            kill(pid, SIGTERM);
            break;
        case 3:
            return 0;
        default:
            printf("Invalid option\n");
        }
    }
    
}