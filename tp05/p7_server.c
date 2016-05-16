#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFFER_SIZE 256

int main(void) {
    int fd1, fd2;
    char buff[BUFFER_SIZE];
    int num1, num2;

    if ((mkfifo("/tmp/myfifo_req", 0660)) == -1) {
        fprintf(stderr, "Failed to create FIFOreq (%d %s)\n", errno, strerror(errno));
        exit(1);
    }

    if ((mkfifo("/tmp/myfifo_ans", 0660)) == -1) {
        fprintf(stderr, "Failed to create FIFOans (%d %s)\n", errno, strerror(errno));
        exit(2);
    }

    fd1 = open("/tmp/myfifo_req", O_RDONLY);
    if (fd1 == -1) {
        fprintf(stderr, "Failed to open FIFOreq (%d %s)\n", errno,  strerror(errno));
        exit(3);
    }

    fd2 = open("/tmp/myfifo_ans", O_WRONLY);
    if (fd2 == 1) {
        fprintf(stderr, "Failed to open FIFOans (%d %s)\n", erro, strerror(errno));
        exit(4);
    }

    int done = 0;
    while ((read(fd, buff, BUFFER_SIZE)) > 0 && !done) {
        num1 = atoi(strtok(buff, " "));
        num2 = atoi(strtok(NULL, " "));
        if (num1 == 0 && num2 == 0) {
            done = 1;
        }
        else {
            int sum = num1 + num2;

        }
    }

}
