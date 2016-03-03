#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(void) {
	int fd;
	char *text1 = "AAAAA";
	char *text2 = "BBBBB";
	
	// int open(const char *pathname, int flags, mode_t mode)
	// as flags utilizadas neste caso sao as seguintes :
	// O_CREAT : if the file does not exist it will be created
	// O_EXCL : ensure that this call creates the file. if this flag is specified in conjuntion with O_CREAT, and pathname already exists, then open() will fail
	// O_TRUNC : if the file already exists and is a regular file and the open mode allows writing it will be truncated to length 0
	// O_SYNC : the file is opened for synchronous I/O
	// 0600 significa permissao do user para read/write
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
