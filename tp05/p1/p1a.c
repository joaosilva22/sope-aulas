#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define READ 0
#define WRITE 1

int main(void) {
    int fd[2];
    pid_t pid;

    // int pipe(int pipefd[2])
    // pipe() creates a pipe, a unidirectional data channel that can be used for interprocess communication
    // the array pipefd is used to return two file descriptors referring to the ends of the pipe
    // pipefd[0] refers to the read end of the pipe
    // pipefd[1] refers to the write end of the pipe
    if ((pipe(fd)) != 0) {
        fprintf(stderr, "Failed to create the pipe (%d %s)", errno, strerror(errno));
        exit(1);
    }

    pid = fork();
    if (pid == -1) {
        fprintf(stderr, "Failed to fork the process (%d %s)", errno, strerror(errno));
        exit(2);
    }

    if (pid > 0) {
        int a[2];
        printf("PARENT : \n");
        printf("x y ? ");
        scanf("%d %d", &a[0], &a[1]);
        // int close(int fd)
        // close() closes a file descriptor, so that it no longer refers to any file and may be reused
        close(fd[READ]);
        write(fd[WRITE], a, 2 * sizeof(int));
        close(fd[WRITE]);
    }
    else {
        int b[2];
        close(fd[WRITE]);
        read(fd[READ], b, 2 * sizeof(int));
        printf("SON : \n");
        printf("x + y = %d\n", b[0] + b[1]);
        printf("x - y = %d\n", b[0] - b[1]);
        printf("x * y = %d\n", b[0] * b[1]);
        if (b[1] != 0)
            printf("x / y = %f\n", (double) b[0] / (double) b[1]);
        else
            printf("x / y = (err : dividing by 0)\n");
        close(fd[READ]);
    }

    return 0;
}
