#include <sys/types.h>	//
#include <sys/stat.h>	//
#include <fcntl.h>		// open()
#include <unistd.h>		// close(), lseek()
#include <stdio.h>		// perror()
#include <errno.h>		// errno variable
#include <stdlib.h>		// exit()

int main(void) {
	int fd = open("temp.txt", 0);
	if(fd == -1) {
		perror("open");
		exit(EXIT_FAILURE);
	}

	off_t position = lseek(fd, 0, SEEK_CUR);
	if(position == (off_t) -1) {
		perror("lseek");
	} else {
		fprintf(stdout, "current position of a file is: %d\n", (int) position);
	}

	position = lseek(fd, 0, SEEK_END);
	if(position == (off_t) -1) {
		perror("lseek");
	} else {
		fprintf(stdout, "current position of a file is: %d\n", (int) position);
	}

	position = lseek(fd, 2, SEEK_SET);
	if(position == (off_t) -1) {
		perror("lseek");
	} else {
		fprintf(stdout, "current position of a file is: %d\n", (int) position);
	}

	close(fd);
	exit(EXIT_SUCCESS);
}
