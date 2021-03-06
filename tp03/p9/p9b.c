#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[], char *envp[]) {
	pid_t pid;
	int status;

	if (argc != 2) {
		printf("usage : %s dirname\n", argv[0]);
		exit(1);
	}

	pid = fork();
	if (pid > 0) {
		printf("My child is going to execute comand \"ls -laR %s\"\n", argv[1]);
		wait(&status);
		// WEXITSTATUS(status) : returns the exit status of the child
		printf("My son exited with EXIT CODE = %d\n", WEXITSTATUS(status));
		if (WIFEXITED(status))
			printf("programa terminou normalmente ...\n");
		if (WIFSIGNALED(status))
			printf("programa terminou atraves de um sinal ...\n");
	} else  if (pid == 0) {
		execlp("ls", "ls", "-laR", argv[1], NULL);
		printf("Command not executed !\n");
		exit(1);
	}
	exit(0);
}
