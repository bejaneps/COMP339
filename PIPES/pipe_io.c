/*

Program to write and read two messages using pipe.

*/

#include <stdio.h>
#include <unistd.h>

int main(void)
{	
	int pipefds[2], returnstatus;
	char writemessages[2][20] = {"Hi", "Hello"}, readmessage[20];

	if((returnstatus = pipe(pipefds)) == -1)
	{
		printf("Unable to create a pipe.\n");
		return -1;
	}

	printf("Writing to pipe - Message 1: %s\n", writemessages[0]);
	write(pipefds[1], writemessages[0], sizeof(writemessages[0]));

	read(pipefds[0], readmessage, sizeof(readmessage));
	printf("Reading from pipe - Message 1: %s\n", readmessage);

	printf("Writing to pipe - Message 2: %s\n", writemessages[1]);
	write(pipefds[1], writemessages[1], sizeof(writemessages[1]));

	read(pipefds[0], readmessage, sizeof(readmessage));
	printf("Reading from pipe - Message 2: %s\n", readmessage);

	return 0;
}