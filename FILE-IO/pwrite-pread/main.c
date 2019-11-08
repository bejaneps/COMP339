#define _XOPEN_SOURCE 500

#include <sys/types.h>	// ""
#include <sys/stat.h>	// ""
#include <fcntl.h>		// open()
#include <unistd.h>		// pwrite(), pread(), lseek()
#include <stdio.h>		// perror()
#include <errno.h>		// errno variable
#include <stdlib.h>		// exit()
#include <string.h>		// strlen()

int main(void) {
	int fd = open("temp.txt", O_RDWR);
	if(fd == -1) {
		perror("open");
		exit(EXIT_FAILURE);
	}

	char wBuffer[] = "78";
	int bufSize = strlen(wBuffer);

	ssize_t len = pwrite(fd, wBuffer, bufSize, (off_t) 2);
	if(unlikely(len == -1)) {
		perror("pwrite");
	} else if(len == 0) {
		fprintf(stderr, "no bytes were written.\n");
	} else if(len < bufSize) {
		fprintf(stderr, "less bytes were written.\n");
	} else {
		fprintf(stdout, "%d bytes were written to file.\n", (int) len);
	}

	char *rBuffer = (char *)malloc(6);
	if(!rBuffer) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	rBuffer[5] = '\0';

	bufSize = strlen(rBuffer);

	len = pread(fd, rBuffer, 5, (off_t) 0);
	if(unlikely(len == -1)) {
		perror("pread");
	} else if(len == 0) {
		fprintf(stderr, "bytes were not red, EOF.\n");
	} else if(len < bufSize) {
		fprintf(stderr, "less bytes were red.\n");
	} else {
		fprintf(stdout, "bytes were red successfully -> %s\n", rBuffer);
	}
	
	free(rBuffer);
	close(fd);

	exit(EXIT_SUCCESS);
}