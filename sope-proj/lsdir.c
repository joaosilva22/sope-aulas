#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

int main(void) {
	char cwd[1024];

	int fd = open("files.txt", O_CREAT | O_WRONLY | O_APPEND, 0600);
	if (fd < 0) {
		fprintf(stderr, "Failed to open files.txt.\n");
		exit(1);
	}

	int _fd1 = dup2(fd, STDOUT_FILENO);
	if (_fd1 == -1) {
		fprintf(stderr, "Failed to redirect output stream (%d %s)\n", errno, strerror(errno));
		exit(2);
	}
	int _fd2 = dup2(fd, STDERR_FILENO);
	if (_fd2 == -1) {
		fprintf(stderr, "Failed to redirect error stream (%d %s)\n", errno, strerror(errno));
		exit(3);
	}
	close(fd);

	if (getcwd(cwd, sizeof(cwd)) == NULL) {
		fprintf(stderr, "Failed to get current working directory (%d %s)\n", errno, strerror(errno));
		exit(4);
	}
	fprintf(stdout, "%s\n", cwd);
	fflush(stdout);
	execlp("ls", "ls", "-ltrpB", NULL);

	return 0;
}
