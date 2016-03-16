#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void sigint_handler(int signo) {
	printf("In SIGINT handler ...\n");
}

int main(void) {
	// sighandler_t signal(int signum, sighandler_t handler)
	// signal() sets the disposition of the signal signum to handler
	// which is either SIG_IGN, SIG_DFL or the adress of a programmer-defined function ("a signal handler")
	if (signal(SIGINT, sigint_handler) < 0) {
		fprintf(stderr, "Unable to install SIGINT handler\n");
		exit(1);
	}
	printf("Sleeping for 30 seconds ...\n");
	sleep(30);
	printf("Waking up ...\n");
	exit(0);
}
