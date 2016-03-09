#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

// on Unix and Unix-like computer OS a zombie process or defunct process is a process that has completed execution (via the exit() system call) but still has an entry in the process table
// it is a process in the terminated state. this occurs for child processes, where the entry is still needed to allow the parent process to read its child exit status
// once the exit status is read via the wait() system call, the zombie's entry is removed from the process table

int main(void) {
	pid_t pid;
	int i, j;

	printf("I'm process %d. My parent is %d.\n", getpid(), getppid());
	for (i = 1; i <= 3; i++) {
		pid = fork();
		if (pid < 0) {
			printf("fork error");
			exit(1);
		} else if (pid == 0) {
			printf("Im process %d. My parent is %d. I'm going to work for 1 second ...\n", getpid(), getppid());
			sleep(1); // simulando o trabalho do filho
			printf("I'm process %d. My parent is %d. I finished my work\n", getpid(), getppid());
			exit(0);
		} else {
			for (j = 1; j <= 10; j++) {
				sleep(1);
				printf("father working ...\n");
			}
		}
	}
	exit(0);
}
