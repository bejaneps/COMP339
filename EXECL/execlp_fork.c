//for printf, scanf
#include <stdio.h>

//for fork, getpid, getppid
#include <unistd.h>

//for getpid, getppid, wait
#include <sys/types.h>

//for wait
#include <wait.h>

int main() {
	
	//create a new process
	int pid = fork();
	
	//print process id, and parent process id
	printf("My id = %d, Parent id = %d\n", getpid(), getppid());
	
	//if less than zero, it means there is an error
	if(pid < 0) {
		perror("Cannot fork");
		return -1;
	}
	
	//child process
	if(pid == 0) {
		execlp("ls", "ls", "-l", NULL);
		
		//this line will never be reached unless there is an error
		perror("Exec error");
		return -1;
	}
	
	//parent process
	if(pid > 0) {
		int status;
		
		//wait for child to terminate
		int cid = wait(&status);
		
		//something wrong happened
		if(cid < 0) {
			perror("Wait failed");
			
			return -2;
		}
		
		if(WIFEXITED(status)) {
			printf("Child %d has exited with code %d\n", cid, WEXITSTATUS(status));
		}
		else {
			printf("Child %d has crashed\n", pid);
			printf("Return value was: %d\n", cid);
		}
	}
	
	return 0;
}