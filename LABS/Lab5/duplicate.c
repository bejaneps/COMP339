#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
	int fd1,fd2;
	fd1 = open("FirstFile.txt", O_RDONLY | O_CREAT | O_TRUNC, S_IRWXU | S_IRWXO);
	close(2);
	dup(fd1); // or dup2(fd1, 2) 
	while(1) ;

	return 0;
}


/*

./execfile &
cd /proc/pid/fd
ls -ltr

*/