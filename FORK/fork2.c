#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void) {
	int pid = fork();

	if(pid) {
		sleep(1);
		printf("y");
	}
	else {
		printf("x");
		return 0;
	}
}