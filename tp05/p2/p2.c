#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#define READ 0
#define WRITE 1

int main(void) {
    int fd1[2], fd2[2];
    pid_t pid;

    if ((pipe(fd1)) != 0) {
        fprintf(stderr, "Failed to create the pipe (%d %s)", errno, strerror(errno));
        exit(1);
    }

    if ((pipe(fd2)) != 0) {
        fprintf(stderr, "Failed to create the pipe (%d %s)", errno, strerror(errno));
        exit(2);
    }

    pid = fork();

    if (pid == -1) {
        fprintf(stderr, "Failed to fork the process (%d %s)", errno, strerror(errno));
        exit(3);
    }

    if (pid > 0) {
        int a[2], r;

        close(fd1[READ]);
        close(fd2[WRITE]);

        printf("x y ? ");
        scanf("%d %d", &a[0], &a[1]);

        write(fd1[WRITE], &a, 2 * sizeof(int));
        close(fd1[WRITE]);

        read(fd2[READ], &r, sizeof(int));
        close(fd2[READ]);

        printf("x + y = %d\n", r);
    }
    else {
        int b[2], sum;

        close(fd1[WRITE]);
        close(fd2[READ]);

        read(fd1[READ], &b, 2 * sizeof(int));
        close(fd1[READ]);

        sum = b[0] + b[1];
        write(fd2[WRITE], &sum, sizeof(int));
        close(fd2[WRITE]);
    }
    return 0;
}
