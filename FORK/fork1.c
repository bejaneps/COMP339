#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void) {
	int pid = fork();
	
	if(pid) {
		printf("x");
	}
	else {
		printf("y");
		sleep(1);
	}
	
	return 0;
}