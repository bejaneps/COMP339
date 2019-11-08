/* 

A program that sums an array of integers by using 4 threads

*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

//array of million numbers
int data[1000000];
#define THC 4	//numbers of threads that we are using in program
int result[THC] = {}; // summation result of all threads

void *sum(void *d)
{
	int index = *(int *)d;
	for (int i = index; i < 1000000; i += THC) 
	{
		result[index] += data[i];
	}

	return NULL;
}

int main(void)
{
	srandom((unsigned)time(NULL));
	for(int i = 0; i < 1000000; i++)
	{
		data[i] = rand() % 100 + 1;
	}

	pthread_t th[THC];
	int indices[THC];

	for(int i = 0; i < THC; i++)
	{
		indices[i] = i;
		pthread_create(&th[i], NULL, &sum, &indices[i]);
	}

	int total = 0;
	for(int i = 0; i < THC; i++)
	{
		pthread_join(th[i], NULL);
		total += result[i];
	}

	fprintf(stdout, "Summation of random numbers is: %d\n", total);

	return 0;
}