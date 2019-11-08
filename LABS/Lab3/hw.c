/*

Create a program that runs users command. Program will continue until selection is equal to exit. This program must support the following commands:
	1. files: Run the ls command.
	2. new directory: run mkdir command after asking for the name of the new directory.
	3. hello: write and compile a simple program that says hello. When this option is requested, the main program must run this simple program. (Use the execl () system call for this)
	4. exit: terminates program

*/

#include <sys/types.h>
#include <stdlib.h>	//exit()
#include <stdio.h>	//printf(), perror(), scanf(), fflush()
#include <errno.h>	//errno variable
#include <unistd.h>	//fork(), execl(), execlp()
#include <wait.h>	//wait()

int main(void)
{
	int choice, ret;
	pid_t pid;
	char dir_name[30];

	while(1)
	{
		printf("Select one of the options to execute:\n");
		printf("1. ls command\n2. mkdir command\n3. hello command\n4. exit\n");
		printf(">> ");
		scanf("%d", &choice);
		
		if(choice == 4)
		{
			printf("You have chosen option 4 - exit. Goodbye !\n");
			exit(EXIT_SUCCESS);
		}
		else if(choice == 1)
		{
			printf("You have chosen option 1 - ls. I'll print directory files.\n");

			pid = fork();

			if (pid == -1) {
				perror(strerror(errno));
			} else if (pid == 0) {
				ret = execlp("ls", "ls", "-l", (char *)NULL);
				if(ret == -1) {
					perror(strerror(errno));
					exit(EXIT_FAILURE);
				}
			} else {
				wait(NULL);
			}
		}
		else if(choice == 2)
		{
			printf("You have chosen option 2 - mkdir. I'll create new directory.\n");
			printf("Enter new directory name: ");
			scanf("%s", dir_name);

			pid = fork();

			if (pid == -1) {
				perror(strerror(errno));
			} else if (pid == 0) {
				ret = execlp("mkdir", "mkdir", dir_name, (char *)NULL);
				if(ret == -1) {
					perror(strerror(errno));
					exit(EXIT_FAILURE);
				}
			} else {
				wait(NULL);
			}
		}
		else if(choice == 3)
		{
			printf("You have chosen option 3 - hello. I'll print hello to stdout.\n");

			if (pid == -1) {
				perror(strerror(errno));
			} else if (pid == 0) {
				ret = execl("/home/bezhan/Programming/local-storage/C Programming/systems-programming/old/LABS/Lab3/./hello_world", "./hello_world", (char *)NULL);
				if(ret == -1)
					perror(strerror(errno));
				exit(0);
			} else {
				wait(NULL);
			}
		}
		else
		{
			printf("Wrong choice. Please try again.\n\n");
			fflush(stdin);
		}
	}

	return 0;
}