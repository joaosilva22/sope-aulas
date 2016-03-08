#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void) {
	pid_t pid;
	pid = fork();

	if (pid == -1) {
		perror("fork ");
		exit(1);
	}

	// child process
	if (pid == 0) {
		write(STDOUT_FILENO, "Hello", 5);
	// parent process
	} else {
		// the wait() system call suspends execution of the calling process until one its children terminates
		wait(NULL);
		write(STDOUT_FILENO, " world !\n", 9);
	}

	return 0;
}
