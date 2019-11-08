/*

This program creates 1 million random numbers and uses multiple threads to check if they are prime. You may run this program with any number of threads. Additionally, this program calculates the amount of the time passed and shows that information.

*/

#include <pthread.h> //pthread
#include <stdio.h> //printf()
#include <stdlib.h> //rand()
#include <math.h> //sqrt()
#include <sys/time.h> //time()


struct entry {
	unsigned number;
	int result; //0 -> not prime,  -> prime
};

#define N 1000000

//entries to be processed
struct entry entries[N] = {};

//next entry to be processed
int next = 0;

//mutex to lock next entry
pthread_mutex_t mtx;


//this function returns 1 if the given number is prime
int isprime(int number) {
	int i;
	for(i = 2; i<(int)sqrt(number); i++) {
		if(number%i == 0) return 0;
	}
	
	return 1;
}

//this function fetches entries one by one and calls is prime function, which takes
//a long time to execute. But this duration depends on the number and can change
//from very short to very long.
void *perform_prime(void *param) {
	
	while(next < N) {
		//lock the mutex
		pthread_mutex_lock(&mtx);
		
		//get our own number and increment. This operation should be done in serial
		int myentry = next;
		next++;
		
		//unlock the mutex to allow other threads to work
		pthread_mutex_unlock(&mtx);
		
		//perform operation. this is outside the critical section
		entries[myentry].result = isprime(entries[myentry].number);
	}
	
	return NULL;
}

int main(int argc, char *argv[]) {
	int threadc = 4;
	//if present use the number of threads given by the user
	if(argc == 2) {
		//convert argument to integer
		threadc = atoi(argv[1]);
	}
	
	// maximum number of threads
	if(threadc > 16) {
		threadc = 16;
	}
	
	printf("This operation might take while, please wait...\n");
	
	pthread_t threads[16];
	int i;
	
	pthread_mutex_init(&mtx, NULL);
	
	struct timespec start, end;
	clock_gettime(CLOCK_MONOTONIC_RAW, &start);
	
	for(i=0; i<N; i++) {
		//produce a large random number
		entries[i].number = rand() * rand();
		entries[i].result = -1;
	}
	
	//create threads
	for(i=0; i<threadc; i++) {
		pthread_create(&threads[i], NULL, &perform_prime, NULL);
	}
	
	//join them
	for(i=0; i<threadc; i++) {
		pthread_join(threads[i], NULL);
	}
	
	//get time elapsed
	clock_gettime(CLOCK_MONOTONIC_RAW, &end);
	printf("Operation took %lf seconds\n", (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0);
	
	//check if all numbers are done
	for(i=0; i<N; i++) {
		if(entries[i].result == -1) {
			printf("There is a problem in %d\n", i);
			exit(1);
		}
	}
	
	//display success message
	printf("All numbers are done.\n");
	
	return 0;
}