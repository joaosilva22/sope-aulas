#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main(void) {
	pid_t pid, pid2;
	pid = fork();

	if (pid == -1) {
		perror("fork ");
		exit(1);
	}
	
	// parent process
	if (pid > 0) {
		write(STDOUT_FILENO, "Hello", 5);
		wait(NULL);
	// child process
	} else {
		pid2 = fork();

		if (pid2 == -1) {
			perror("fork ");
			exit(1);
		}

		if (pid2 > 0) {
			write(STDOUT_FILENO, " my", 3);
			wait(NULL);
		// child of child process
		} else {
			write(STDOUT_FILENO, " friends!\n", 10);
		}
	}
	return 0;
}
