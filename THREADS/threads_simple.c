/*

In this example two separate threads sum odd and even numbers separately. This program shows the value return and parallel execution capabilities.

*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

//Sums odd
void *sum_odd(void *param) {
	int i, sum = 0;
	for(i = 1; i<1000; i+=2) {
		sum += i;
	}
	
	//create data buffer to return
	int *data = (int*)malloc(sizeof(int));
	
	*data = sum;
	
	return (void*)data;
}

//Sums even numbers
void *sum_even(void *param) {
	int i, sum = 0;
	for(i = 2; i<1000; i+=2) {
		sum += i;
	}
	
	//create data buffer to return
	int *data = (int*)malloc(sizeof(int));
	
	*data = sum;
	
	return (void*)data;
}

int main() {
	pthread_t t1, t2;
	int *v1, *v2;
	
	pthread_create(&t1, NULL, &sum_odd, NULL);
	pthread_create(&t2, NULL, &sum_even, NULL);
	pthread_join(t1, (void*)&v1);
	pthread_join(t2, (void*)&v2);
	
	printf("Sum of odd and even numbers from 1 to 1000 is: %d\n", *v1+*v2);
	
	return 0;
}