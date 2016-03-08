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
		write(STDOUT_FILENO, " world !\n", 9);
	// parent process
	} else {
		write(STDOUT_FILENO, "Hello", 5);
	}
	return 0;
}
