#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void){
	//printf("My ID is: %d \n", (int) getpid());

	pid_t pid= fork();
	printf("I am %d\n", (int) pid);
	
	if(pid == 0){ 
		printf("Child\n");
		sleep(5);
		exit(0);
	}
	else if(pid < 0) {
		printf("Error\n");
	}
	else {
		printf("Parent\n");
		wait(NULL);
	}

	return 0;
}

