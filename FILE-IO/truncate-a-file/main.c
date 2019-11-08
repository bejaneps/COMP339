#include <sys/stat.h>	// ""
#include <fcntl.h>		// open()
#include <unistd.h>		// truncate(), ftruncate()
#include <sys/types.h>	// ""
#include <stdio.h>		// perror(), fprintf()
#include <errno.h>		// errno variable
#include <stdlib.h>		// exit()

int main(void) {
	int fd = open("temp.txt", O_WRONLY);
	if(fd == -1) {
		perror("open");
		exit(EXIT_FAILURE);
	}

	int len = ftruncate(fd, 10);
	if(len == -1) {
		perror("ftruncate");
	} else {
		fprintf(stdout, "file was truncated successfully.\n");
	}

	exit(EXIT_SUCCESS);
}