#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <wait.h>

int main(int argc, char *argv[]) {
    DIR *dir;
    struct dirent *dirent;
    struct stat stat;
    pid_t pid, pid_terminated;
    int status;
    char cwd[1024];

    if (argc != 3) {
        fprintf(stderr, "Usage : lsall <dir-path> <dest-path>\n");
        exit(1);
    }

    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        fprintf(stderr, "Failed to get current working directory (%d %s)\n", errno, strerror(errno));
        exit(2);
    }

    dir = opendir(argv[1]);
    if (dir == NULL) {
        fprintf(stderr, "Failed to open directory '%s' (%d %s)\n", argv[1], errno, strerror(errno));
        exit(3);
    }

    while ((dirent = readdir(dir)) != NULL) {
        if (strcmp(dirent->d_name, ".") != 0 && strcmp(dirent->d_name, "..") != 0) {
            char dir_path[1024];
            strcpy(dir_path, argv[1]);
            strcat(dir_path, dirent->d_name);
            if ((lstat(dir_path, &stat)) != 0) {
                fprintf(stderr, "Failed to stat file '%s%s' (%d %s)\n", argv[1], dirent->d_name, errno, strerror(errno));
                exit(4);
            }

            if (S_ISDIR(stat.st_mode)) {
                strcat(dir_path, "/");
                pid = fork();
                if (pid == -1) {
                    fprintf(stderr, "Failed to fork the process (%d %s)\n", errno, strerror(errno));
                    exit(5);
                }

                if (pid > 0) {
                    pid_terminated = wait(&status);
                    printf("Child %d (%s) terminated with exit code %d\n", pid_terminated, dirent->d_name, WEXITSTATUS(status));
                }
                else {
                    char lsall[strlen(cwd) + 7];
                    strcpy(lsall, cwd);
                    strcat(lsall, "/lsall");

                    execlp(lsall, lsall, dir_path, argv[2], NULL);
                    fprintf(stderr, "Failed to execute %s %s %s\n", lsall, dir_path, argv[2]);
                    exit(6);
                }
            }
        }
    }

    if ((closedir(dir)) != 0) {
        fprintf(stderr, "Failed to close directory '%s' (%d %s)\n", argv[1], errno, strerror(errno));
        exit(7);
    }

    char lsdir[strlen(cwd) + 7];
    strcpy(lsdir, cwd);
    strcat(lsdir, "/lsdir");

    execlp(lsdir, lsdir, argv[1], argv[2], NULL);
    fprintf(stderr, "Failed to execute %s %s %s\n", lsdir, argv[1], argv[2]);
    exit(8);

    return 0;
}
