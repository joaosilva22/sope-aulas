#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    DIR *dir;
    struct dirent *dirent;
    struct stat stat;
    int fd;
    struct tm *tm;

    if (argc != 3) {
        fprintf(stderr, "Usage : lsdir <dir-path> <dest-path>\n");
        exit(1);
    }

    fd = open(argv[2], O_CREAT | O_WRONLY | O_APPEND, 0600);
    if (fd == -1) {
        fprintf(stderr, "Failed to open file '%s' (%d %s)\n", argv[2], errno, strerror(errno));
        exit(2);
    }

    if ((dup2(fd, STDOUT_FILENO)) == -1) {
        fprintf(stderr, "Failed to dup file descriptor (%d %s)", errno, strerror(errno));
        exit(3);
    }

    if ((close(fd)) != 0) {
        fprintf(stderr, "Failed to close file descriptor (%d %s)", errno, strerror(errno));
        exit(4);
    }

    dir = opendir(argv[1]);
    if (dir == NULL) {
        fprintf(stderr, "Failed to open directory '%s' (%d %s)\n", argv[1], errno, strerror(errno));
        exit(5);
    }

    while ((dirent = readdir(dir)) != NULL) {
        char file_path[1024];
        strcpy(file_path, argv[1]);
        strcat(file_path, dirent->d_name);
        if ((lstat(file_path, &stat)) != 0) {
            fprintf(stderr, "Failed to stat file '%s' (%d %s)\n", file_path, errno, strerror(errno));
            exit(6);
        }

        if (!(S_ISDIR(stat.st_mode))) {
            if (S_ISREG(stat.st_mode)) {
                if ((tm = gmtime(&stat.st_mtime)) == NULL) {
                    fprintf(stderr, "Failed to read time (%d %s)\n", errno, strerror(errno));
                    exit(7);
                }

                printf("%d %d %d %d %d %d,%s,%s,%d,%o,%d,\n", 1900 + tm->tm_year, 1 + tm->tm_mon, tm->tm_mday, 1 + tm->tm_hour, tm->tm_min, tm->tm_sec, file_path, dirent->d_name, (int) stat.st_size, stat.st_mode, (int) stat.st_ino);
            }
        }
    }

    if ((closedir(dir)) != 0) {
        fprintf(stderr, "Failed to close directory '%s' (%d %s)\n", argv[1], errno, strerror(errno));
        exit(8);
    }

    return 0;
}
