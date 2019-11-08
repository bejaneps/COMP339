#include <sys/types.h>	// ""
#include <sys/stat.h>	// ""
#include <fcntl.h>		// open()
#include <unistd.h>		// write(), fsync()
#include <stdio.h>		// perror(), fprintf()
#include <stdlib.h>		// exit()
#include <errno.h>		// errno variable
#include <string.h>		// strlen()

int main(void) {
	int fd = creat("temp.txt", 0600);	// rw permission for user
	if(fd == -1) {
		perror("creat");
		exit(EXIT_FAILURE);
	}

	char buffer[] = "abcde";
	int bufSize = strlen(buffer);

	ssize_t len = write(fd, buffer, bufSize);
	if(len == (ssize_t) -1) {
		perror("write");

		close(fd);
		exit(EXIT_FAILURE);
	} else if(len == 0) {
		fprintf(stderr, "no bytes written, EOF.\n");
	} else if(len < bufSize) {
		fprintf(stderr, "less bytes were written to file.\n");
	} else {
		fprintf(stdout, "written %d bytes to file.\n", bufSize);
	}

	//flush changes to disk
	if((fsync(fd)) == -1) {
		if(errno == EINVAL) {
			if(fdatasync(fd) == -1) {	//in case if fsync fails, use fdatasync
				perror("fdatasync");
			}
		} else {
			perror("fsync");
		}
	}

	close(fd);
	exit(EXIT_SUCCESS);
}