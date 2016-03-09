#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char *argv[], char *envp[]) {
	pid_t pid;
	if (argc != 2 && argc != 3) {
		printf("usage : %s <dirname> OR %s <dirname> <filename>\n", argv[0], argv[0]);
		exit(1);
	}

	pid = fork();
	if (pid > 0) {
		printf("My child is going to execute comand \"ls -laR %s\"\n", argv[1]);
	} else  if (pid == 0) {
		if (argc == 3) {
			int fd;
			fd = open(argv[2], O_CREAT | O_WRONLY, 0600);
			dup2(fd, STDOUT_FILENO); 
		}
		execlp("ls", "ls", "-laR", argv[1], NULL);
		printf("Command not executed !\n");
		exit(1);
	}
	exit(0);
}
