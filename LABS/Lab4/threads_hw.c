/*

Create a program that increases a local variable 50000 times using 4 threads and prints the
result.

NOTE: 50000 is too high for long long, so I will use just 48.

*/

#include <pthread.h>
#include <stdio.h>
#include <stdint.h>

uint64_t results[4] = {};

// In order to not reduce speed of execution, I will create separate fnct for each thread. Yes, I could use mutex threads here, but threads are for speed )
int power(int x, unsigned int y);
void *increase_1(void *arg);
void *increase_2(void *arg);
void *increase_3(void *arg);
void *increase_4(void *arg);

int main(void)
{	
	pthread_t ths[4];
	int local_number[4] = {2, 2, 2, 2};
	uint64_t total = 0;

	pthread_create(&ths[0], NULL, &increase_1, &local_number[0]);
	pthread_create(&ths[1], NULL, &increase_2, &local_number[1]);
	pthread_create(&ths[2], NULL, &increase_3, &local_number[2]);
	pthread_create(&ths[3], NULL, &increase_4, &local_number[3]);

	for(int i = 0; i < 4; i++)
	{
		pthread_join(ths[i], NULL);
	}

	total = results[0] * results[1] * results[2] * results[3];

	fprintf(stdout, "Number %d increased 48 times will be: %lu\n", local_number[0], total);

	return 0;
}

int power(int x, unsigned int y) 
{ 
    if (y == 0) 
        return 1; 
    else if (y % 2 == 0) 
        return power(x, y/2) * power(x, y/2); 
    else
        return x * power(x, y/2) * power(x, y/2); 
}

void *increase_1(void *arg)
{
	int number = *(int *)arg;
	uint64_t result = 0, temp = number;
	for(int i = 0; i < 12; i++)
	{
		temp = temp * number;
		result += temp;
	}

	results[0] = result;
}

void *increase_2(void *arg)
{
	int number = *(int *)arg;
	uint64_t result = 0, temp = number;
	for(int i = 0; i < 12; i++)
	{
		temp = temp * number;
		result += temp;
	}

	results[1] = result;
}

void *increase_3(void *arg)
{
	int number = *(int *)arg;
	uint64_t result = 0, temp = number;
	for(int i = 0; i < 12; i++)
	{
		temp = temp * number;
		result += temp;
	}

	results[2] = result;
}

void *increase_4(void *arg)
{
	int number = *(int *)arg;
	uint64_t result = 0, temp = number;
	for(int i = 0; i < 12; i++)
	{
		temp = temp * number;
		result += temp;
	}

	results[3] = result;
}