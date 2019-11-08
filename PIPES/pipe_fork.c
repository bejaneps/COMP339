/*

Program to write and read two messages through the pipe using the parent and the child processes.

*/

#include <stdio.h>
#include <unistd.h>

int main(void)
{	
	int pipefds[2], returnstatus;
	pid_t pid;
	char writemessages[2][20] = {"Hi", "Hello"}, readmessage[20];

	if((returnstatus = pipe(pipefds)) == -1)
	{
		perror("Unable to create a pipe.\n");
		return -1;
	}

	pid = fork();

	if(pid == 0) // child process
	{
		read(pipefds[0], readmessage, sizeof(readmessage));
		printf("Child process - Reading from pipe - Message 1: %s\n", readmessage);
		read(pipefds[0], readmessage, sizeof(readmessage));
		printf("Child process - Reading from pipe - Message 2: %s\n", readmessage);
	}
	else // parent process
	{
		printf("Parent Process - Writing to pipe - Message 1 is %s\n", writemessages[0]);
      	write(pipefds[1], writemessages[0], sizeof(writemessages[0]));
      	printf("Parent Process - Writing to pipe - Message 2 is %s\n", writemessages[1]);
      	write(pipefds[1], writemessages[1], sizeof(writemessages[1]));
	}

	return 0;
}