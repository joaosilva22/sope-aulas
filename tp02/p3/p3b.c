#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUF_LENGTH 256

int main(int argc, char* argv[]) {
	int src, dst;
	char buf[BUF_LENGTH];

	if ((argc != 2) && (argc != 3)) {
		printf("usage : %s <source> OR %s <source> <destination>\n", argv[0], argv[0]);
		exit(1);
	}

	src = open(argv[1], O_RDONLY);
	if (src < 0) {
		printf("error : could not open file %s\n", argv[1]);
		exit(2);
	}

	if (argc == 3) {
		dst = open(argv[2], O_WRONLY);
		if (dst < 0) {
			printf("error : could not open file %s\n", argv[2]);
			close(src);
			exit(3);
		}
		// dup, dup2, dup3 - duplicate a file descriptor
		// int dup2(int oldfd, int newfd)
		// dup2() makes newfd be the copy of oldfd, closing newfd first if necessary
		dup2(dst, STDOUT_FILENO);
	}

	int num = 0;
	while ((num = read(src, buf, BUF_LENGTH)) > 0) {	
		write(STDOUT_FILENO, buf, num);
	}

	close(src);
	if (argc == 3)
		close(dst);

	return 0;
}	
