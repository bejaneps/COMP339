/*

Write a program that should have child processes, program should wait child processes and this child processes should return random values to program and program should print exit states of child processes.

*/

#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
	pid_t pid;
	int no, wstatus;

	srandom((unsigned)time(NULL));
	pid = fork();

	if(pid == -1)
		perror(strerror(errno));
	else if(pid == 0)
	{
		return rand() + 1;
	}
	else
	{
		printf("Waiting for child process..\n");
		no = wait(&wstatus);
		printf("child process id = %d returned %d.\n", no, WEXITSTATUS(wstatus));
	}

	return 0;
}