/*

Program that simultaneously runs 2 functions using mutex threads

*/

#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>


pthread_mutex_t mtx_print;

void *fn1(void *d)
{
	int fd = open("my.txt", O_RDONLY);
	char c;
	int count = 0, r;

	while((r = read(fd, &c, 1)) > 0)
		count++;

	pthread_mutex_lock(&mtx_print);
	printf("my.txt, size = %d\n", count);
	pthread_mutex_unlock;

	return NULL;
}

void *fn2(void *d) 
{
	char *name = getenv("USER");
	pthread_mutex_lock(&mtx_print);
	printf("Hello, %s\n", name);
	pthread_mutex_unlock(&mtx_print);

	return NULL;
}

int main(void)
{	
	pthread_mutex_init(&mtx_print, NULL);
	pthread_t t1, t2;
	pthread_create(&t1, NULL, &fn1, NULL);
	pthread_create(&t2, NULL, &fn2, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	return 0;
}