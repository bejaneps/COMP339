#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void){
	pid_t process = fork();

	if(process > 0) {
		printf("I am the the parent and my ID is: %d\n", (int) process);
		wait(NULL);
		printf("Now I can work!\n");
	}
	else if(process == 0) {
		printf("I am the child and my ID is: %d\n", (int) process);
		sleep(5);
		printf("I woke up !\n");
	}
	else {
		perror("Error!\n");
	}

	return 0;
}

