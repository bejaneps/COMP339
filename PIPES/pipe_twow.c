/*

Achieving two-way communication using pipes.

*/

#include <stdio.h>
#include <unistd.h>

int main(void)
{
	int pipe_fds1[2], pipe_fds2[2], return_status1, return_status2, pid;
	char pipe1_write_message[20] = "Hi", pipe2_write_message[20] = "Hello", read_message[20];

	returnstatus1 = pipe(pipe_fds1);

	return 0;
}