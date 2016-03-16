#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void sigint_handler(int signo) {
	printf("Entering SIGINT handler ...\n");
	sleep(10);
	printf("Exiting SIGINT handler ...\n");
}

void sigterm_handler(int signo) {
	printf("Entering SIGTERM handler ...\n");
	printf("Exiting SIGTERM handler ...\n");
}

int main(void) {
	struct sigaction action;
	action.sa_handler = sigint_handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;


	struct sigaction action1;
	action1.sa_handler = sigterm_handler;
	sigemptyset(&action1.sa_mask);
	action1.sa_flags = 0;

	if (sigaction(SIGINT, &action, NULL) < 0) {
		fprintf(stderr, "Unable to install SIGINT handler\n");
		exit(1);
	}

	if (sigaction(SIGTERM, &action1, NULL) < 0) {
		fprintf(stderr, "Unable to install SIGTERM handler\n");
		exit(2);
	}		
		
	printf("Try me with CTRL-C ...\n");
	while(1) pause();
	exit(0);
}
