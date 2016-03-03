#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(void) {
	int fd;
	char *text1 = "AAAAA";
	char *text2 = "BBBBB";
	
	fd = open("f1.txt", O_CREAT|O_EXCL|O_TRUNC|O_WRONLY|O_SYNC, 0600);
	if (fd < 0) {
		perror("f1.txt ");
		exit(1);
	}
	if ((write(fd, text1, 5)) < 0) {
		perror("write() ");
		exit(2);
	}
	if ((write(fd, text2, 5)) < 0) {
		perror("write() ");
		exit(2);
	}
	close(fd);
	return 0;
}
