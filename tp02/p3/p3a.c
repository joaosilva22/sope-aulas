#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUF_LENGTH 256

int main(int argc, char* argv[]) {
	int src;
	char buf[BUF_LENGTH];

	if (argc != 2) {
		printf("usage : %s <source> \n", argv[0]);
		exit(1);
	}

	src = open(argv[1], O_RDONLY);

	if (src < 0) {
		printf("error : could not open file %s\n", argv[1]);
		exit(2);
	}

	int num = 0;
	while ((num = read(src, buf, BUF_LENGTH)) > 0) {	
		write(STDOUT_FILENO, buf, num);
	}

	close(src);

	return 0;
}	
