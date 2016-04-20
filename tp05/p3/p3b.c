#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define READ 0
#define WRITE 1

int main(int argc, char *argv[]) {
    int fd[2];
    pid_t pid;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input-file>\n", argv[0]);
        exit(1);
    }

    if ((pipe(fd)) != 0) {
        fprintf(stderr, "Failed to create pipe (%d %s)\n", errno, strerror(errno));
        exit(2);
    }

    pid = fork();
    if (pid == -1) {
        fprintf(stderr, "Failed to fork process (%d %s)\n", errno, strerror(errno));
        exit(3);
    }

    if (pid > 0) {
        close(fd[READ]);
        if ((dup2(fd[WRITE], STDOUT_FILENO)) == -1) {
            fprintf(stderr, "Failed to copy file descriptor (%d %s)\n", errno, strerror(errno));
            exit(4);
        }
        close(fd[WRITE]);
        execlp("cat", "cat", argv[1], NULL);
        fprintf(stderr, "Failed to execlp cat\n");
    }
    else {
        close(fd[WRITE]);
        if ((dup2(fd[READ], STDIN_FILENO)) == -1) {
            fprintf(stderr, "Failed to copy file descriptor (%d %s)\n", errno, strerror(errno));
            exit(5);
        }
        close(fd[READ]);
        execlp("sort", "sort", NULL);
        fprintf(stderr, "Failed to execlp sort\n");
    }

    return 0;
}
