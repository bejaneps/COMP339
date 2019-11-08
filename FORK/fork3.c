#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void) {
	for(int i = 0; i < 3; i++) {	// 1.1, 1.2, 1.3
		int pid = fork();			// 2
		if(pid && i % 2)			// 3
			return 0;				// 4
		printf("x");				// 5
	}
}