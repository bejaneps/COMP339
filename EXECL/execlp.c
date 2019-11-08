#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
	printf("Let's execute ls -la command as child process.\n");
	
	if(fork()) {
		wait(NULL);
		printf("Command executed successfully.\n");
	}
	else
		execlp("ls", "ls", "-l", "-a", NULL);
	
	return 0;
}
