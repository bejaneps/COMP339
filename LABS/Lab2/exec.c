#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	int check;
	printf("Calling execl.......!\n");
	check = execl("source", "One", "Two", "Three", NULL);
	check = execlp("top", "top", NULL);
	printf("Failed execl = check = %d\n", check);
	
	return 0;
}
