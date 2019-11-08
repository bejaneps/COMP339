#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int *argc, char *argv[])
{
    pid_t pid;
    int mypipefd[2], ret;
    char buf[20];
    
    ret = pipe(mypipefd);
    
    if(ret == -1)
    {
        perror("Hello World");
        exit(1);
    }

    pid = fork();
    
    if(pid == 0)
    {
        printf("Child Process\n");
        write(mypipefd[1],"data in pipe.", 20);
    }
    else
    {
        printf("Parent Process\n");
        read(mypipefd[0],buf, 20);
        printf("I read using pipe: %s\n", buf);
    }

    return 0;
}
