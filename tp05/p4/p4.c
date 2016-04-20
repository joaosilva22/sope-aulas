#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define READ 0
#define WRITE 1

int main(int argc, char *argv[]) {
    int fd1[2];
    pid_t pid1;

    if (argc != 3) {
        fprintf(stderr, "Usage %s <ls-arg> <grep-arg>\n", argv[0]);
        exit(1);
    }

    if ((pipe(fd1)) == -1) {
        fprintf(stderr, "Failed to create pipe (%d %s)\n", errno, strerror(errno));
        exit(2);
    }

    pid1 = fork();
    if (pid1 == -1) {
        fprintf(stderr, "Failed to fork process (%d %s)\n", errno, strerror(errno));
        exit(3);
    }

    if (pid1 > 0) {
        int fd2[2];
        pid_t pid2;
        close(fd1[READ]);

        if ((pipe(fd2)) == -1) {
            fprintf(stderr, "Failed to create pipe (%d %s)\n", errno, strerror(errno));
            exit(4);
        }

        pid2 = fork();
        if (pid2 == -1) {
            fprintf(stderr, "Failed to fork process (%d %s)\n", errno, strerror(errno));
            exit(5);
        }

        if (pid2 > 0) {
            close(fd1[WRITE]);
            close(fd2[READ]);
            if ((dup2(fd2[WRITE], STDOUT_FILENO)) == -1) {
                fprintf(stderr, "Failed to copy file descriptor (%d %s)\n", errno, strerror(errno));
                exit(6);
            }
            close(fd2[WRITE]);
            execlp("ls", "ls", argv[1], "-laR", NULL);
            fprintf(stderr, "Failed to execlp ls\n");
        }
        else {
            close(fd2[WRITE]);
            if ((dup2(fd2[READ], STDIN_FILENO)) == -1) {
                fprintf(stderr, "Failed to copy file descriptor (%d %s)\n", errno, strerror(errno));
                exit(7);
            }
            close(fd2[READ]);

            if ((dup2(fd1[WRITE], STDOUT_FILENO)) == -1) {
                fprintf(stderr, "Failed to copy file descriptor (%d %s)\n", errno, strerror(errno));
                exit(8);
            }
            close(fd1[WRITE]);
            execlp("grep", "grep", argv[2], NULL);
            fprintf(stderr, "Failed to execlp grep\n");
        }
    }
    else {
        close(fd1[WRITE]);
        if ((dup2(fd1[READ], STDIN_FILENO)) == -1) {
            fprintf(stderr, "Failed to copy file descriptor (%d %s)\n", errno, strerror(errno));
            exit(9);
        }
        close(fd1[READ]);
        execlp("sort", "sort", NULL);
        fprintf(stderr, "Failed to execlp sort\n");
    }

    return 0;
}
