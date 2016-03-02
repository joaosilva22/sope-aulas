#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

#define BUF_LENGTH 256

int main(int argc, char* argv[]) {
	int src, dst;
	char buf[BUF_LENGTH];
	clock_t t1, t2;	

	if (argc != 3) {
		printf("usage : %s <source> <destination>\n", argv[0]);
		exit(1);
	}

	// int open(const char *pathname, int flags)
	// given a pathname for a file, open() returns a file descriptor
	// a small, nonnegative integer for use in subsequent system calls
	// flags must include one of the following :
	// O_RDONLY : read-only
	// O_WRONLY : write-only
	// O_RDWR : read/write
	src = open(argv[1], O_RDONLY);
	dst = open(argv[2], O_WRONLY);

	if (src < 0) {
		printf("error : could not open file %s\n", argv[1]);
		exit(2);
	}

	if (dst < 0) {
		printf("error : could not open file %s\n", argv[2]);	
		exit(3);	
	}
	
	t1 = clock();
	
	// ssize_t read(int fd, void *buf, size_t count)
	// read() attempts to read up count bytes from file descriptor fd into the buffer starting at buff
	// if the file offset is at or past the end of the file no bytes are read
	// if no bytes are read, read() returns 0 and on error, returns -1
	// else returns the number of bytes read
	int num = 0;
	while ((num = read(src, buf, BUF_LENGTH)) > 0) {
		// ssize_t write (int fd, const void *buf, size_t count)
		// write() writes up to count bytes from the buffer pointed at by buf, to the file referred by fd		
		write(dst, buf, num);
	}

	// int close(int fd)
	// close() closes a file descriptor
	close(src);
	close(dst);

	t2 = clock();

	printf("elapsed time : %.5f s\n", (double)(t2-t1)/CLOCKS_PER_SEC);
	return 0;
}	
