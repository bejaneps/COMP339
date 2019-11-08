#include <sys/types.h>		// ""
#include <sys/stat.h>		// ""
#include <fcntl.h>			// open()
#include <stdlib.h>			// malloc()
#include <unistd.h>			// read()
#include <stdio.h>			// perror(), fprintf()
#include <errno.h>			// errno variable

int main(void) {
	int fd = open("temp.txt", 0);
	if(fd == -1) {
		perror("open");
	}

	char *buffer = (char *)malloc(5);
	buffer[4] = '\0';

	unsigned int bytes = 4;
	unsigned long len = read(fd, buffer, bytes);
	if(len == -1) {
		perror("read");
		exit(EXIT_FAILURE);
	} else if(len == 0) {
		fprintf(stderr, "nothing to read, EOF.\n");
	} else if(len < bytes) {
		fprintf(stderr, "not enough data in a file.\n");
	} else {
		fprintf(stdout, "red 4 bytes -> %s\n", buffer);
	}

	close(fd);
	free(buffer);
	return 0;
}