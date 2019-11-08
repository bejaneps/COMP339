/*

Write a C program and determine the results. The program program should print summation of given 3 parameters as shown example below.

./sum 3 5 6
14

*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	int i = 0, sum = 0, val = 0;
	while(i < argc) {
		sum += atoi(argv[i++]);
	}
	
	printf("The sum of integers is: %d\n", sum);

	return 0;
}
