#include <stdio.h>
#include <stdlib.h>
#include <string.h>	
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>	

void sighandler(int signum);
//void catch_sigterm();

int main(void) {
	signal(SIGINT, sighandler);
	signal(SIGTERM, sighandler);
	signal(SIGKILL, sighandler);
	signal(SIGSEGV, sighandler);

	while(1) {
		printf("Process ID: %d\n", getpid());
	}
		
	return 0;
}
/*
void catch_sigterm()
{
    static struct sigaction _sigact;

    memset(&_sigact, 0, sizeof(_sigact));
    _sigact.sa_sigaction = sighandler;
    _sigact.sa_flags = SA_SIGINFO;

    sigaction(SIGTERM, &_sigact, NULL);
}
*/
void sighandler(int signum) {
	write(STDERR_FILENO, "Error", 5);
}

// kill(1 || 2), pause(2), sigaction(2), raise(3)