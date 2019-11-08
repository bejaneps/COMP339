#include <sys/types.h>	// ""
#include <sys/stat.h>	// ""
#include <fcntl.h>		// open()
#include <stdio.h>		// perror()
#include <errno.h>		// errno variable

int main(void) {
	int fd = 0;
	errno = 0;

	fd = open("temp.txt", O_RDONLY);
	if(fd == -1) {
		perror("open");
	}

	close(fd);
	return 0;
}
