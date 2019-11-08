#include <sys/types.h>	// ""
#include <sys/stat.h>	// ""
#include <fcntl.h>		// open()
#include <unistd.h>		// write()
#include <stdio.h>		// perror(), fprintf()
#include <stdlib.h>		// exit()
#include <string.h>		// strlen()
#include <errno.h>		// errno variable

int main(void) {
	int fd = creat("temp.txt", S_IRWXU);

	char buffer[] = "12345";
	int bufSize = strlen(buffer);

	ssize_t len = write(fd, buffer, bufSize);
	if(len == -1) {
		perror("write");
		exit(EXIT_FAILURE);
	} else if(len == 0) {
		fprintf(stderr, "couldn't write to file.\n");
	} else if(len < bufSize) {
		fprintf(stderr, "bytes written is lower than buffer size.\n");
	} else {
		fprintf(stdout, "bytes were written successfuly.\n");
	}

	close(fd);
	exit(EXIT_SUCCESS);
}