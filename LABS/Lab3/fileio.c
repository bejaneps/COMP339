#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void) {
	int fd;
	
	fd = open("testfile.text", O_TRUNC | O_WRONLY | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
	if(fd == -1) {
		perror(strerror(errno));
	}
	
	int num;
	char text[] = "Some text \n\n";
	
	num = write(fd, text, strlen(text));
	if(num == -1) {
		perror(strerror(errno));
	}
	
	return 0;
}
