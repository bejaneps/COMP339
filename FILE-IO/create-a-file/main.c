#include <sys/types.h>	// ""
#include <sys/stat.h>	// ""
#include <fcntl.h>		// creat()
#include <stdio.h>		// perror()
#include <errno.h>		// errno variable
#include <unistd.h>		// close()

int main(void) {
	int fd = creat("temp.txt", S_IRWXU);
	if(fd == -1) {
		perror("creat");
	}

	close(fd);
	return 0;
}