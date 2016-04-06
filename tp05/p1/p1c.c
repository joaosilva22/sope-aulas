#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define READ 0
#define WRITE 1
#define MAX_SIZE 80

int main(void) {
    int fd[2];
    pid_t pid;

    struct input {
        char x[MAX_SIZE], y[MAX_SIZE];
    };

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
        struct input a;
        printf("PARENT : \n");
        printf("x y ? ");
        scanf("%s %s", a.x, a.y);
        // int close(int fd)
        // close() closes a file descriptor, so that it no longer refers to any file and may be reused
        close(fd[READ]);
        write(fd[WRITE], &a, sizeof(struct input));
        close(fd[WRITE]);
    }
    else {
        struct input b;
        close(fd[WRITE]);
        read(fd[READ], &b, sizeof(struct input));
        printf("SON : \n");
        printf("x + y = %d\n", atoi(b.x) + atoi(b.y));
        printf("x - y = %d\n", atoi(b.x) - atoi(b.y));
        printf("x * y = %d\n", atoi(b.x) * atoi(b.y));
        if (atoi(b.y) != 0)
        printf("x / y = %f\n", (double) atoi(b.x) / (double) atoi(b.y));
        else
        printf("x / y = (err : dividing by 0)\n");
        close(fd[READ]);
    }

    return 0;
}
