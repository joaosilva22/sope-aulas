#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <wait.h>
#include <fcntl.h>

#define MAX_LENGTH 1024

int main(int argc, char *argv[]) {
    pid_t pid_lsall, pid_lsall_terminated;
    pid_t pid_sort, pid_sort_terminated;
    int status;
    char cwd[1024];
    int fd;

    FILE *fp1, *fp2;
    char line1[MAX_LENGTH], line2[MAX_LENGTH], line[MAX_LENGTH];

    struct files {
        char *date, *inode, *path, *name, *size, *permissions;
    };
    struct files files[2];

    if (argc != 2) {
        fprintf(stderr, "Usage : rmdup <dir> \n");
        exit(1);
    }

    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        fprintf(stderr, "Failed to get current working directory (%d %s)\n", errno, strerror(errno));
        exit(2);
    }

    char dir_path[1024];
    strcpy(dir_path, argv[1]);
    if ((strcmp(argv[1] + strlen(argv[1]) - 1, "/")) != 0)
        strcat(dir_path, "/");

    char dest_path[1024];
    strcpy(dest_path, argv[1]);
    if ((strcmp(argv[1] + strlen(argv[1]) - 1, "/")) == 0)
        strcat(dest_path, "files.txt");
    else
        strcat(dest_path, "/files.txt");

    fd = open(dest_path, O_CREAT | O_WRONLY | O_TRUNC, 0600);
    if (fd == -1) {
        fprintf(stderr, "Failed to open file '%s' (%d %s)\n", dest_path, errno, strerror(errno));
        exit(3);
    }

    if ((close(fd)) != 0) {
        fprintf(stderr, "Failed to close file descriptor (%d %s)", errno, strerror(errno));
        exit(4);
    }

    pid_lsall = fork();
    if (pid_lsall == -1) {
        fprintf(stderr, "Failed to fork the process (%d %s)", errno, strerror(errno));
        exit(5);
    }

    if (pid_lsall > 0) {
        pid_lsall_terminated = wait(&status);
        printf("Process 'lsall' (%d) terminated with exit code %d\n", pid_lsall_terminated, WEXITSTATUS(status));
    }
    else {
        char lsall[strlen(cwd) + 7];
        strcpy(lsall, cwd);
        strcat(lsall, "/lsall");

        execlp(lsall, lsall, dir_path, dest_path, NULL);
        fprintf(stderr, "Failed to execute %s %s\n", lsall, argv[1]);
        exit(6);
    }

    pid_sort = fork();
    if (pid_sort == -1) {
        fprintf(stderr, "Failed to fork the process (%d %s)", errno, strerror(errno));
        exit(7);
    }

    if (pid_sort > 0) {
        pid_sort_terminated = wait(&status);
        printf("Process 'sort' (%d) terminated with exit code %d\n", pid_sort_terminated, WEXITSTATUS(status));
    }
    else {
        execlp("sort", "sort", "-k1n", "-k2n", "-k3n", "-k4n", "-k5n", "-k6n", dest_path, "-o", dest_path, NULL);
        fprintf(stderr, "Failed to execute sort");
        exit(8);
    }

    fp1 = fopen(dest_path, "r");
    if (fp1 == NULL) {
        fprintf(stderr, "Failed to open file %s (%d %s)\n", dest_path, errno, strerror(errno));
        exit(9);
    }
    fp2 = fopen(dest_path, "r");
    if (fp2 == NULL) {
        fprintf(stderr, "Failed to open file %s (%d %s)\n", dest_path, errno, strerror(errno));
        exit(10);
    }

    int inodes_size = 0, inodes_index = 0;
    while ((fgets(line, MAX_LENGTH, fp1)) != NULL) {
        inodes_size++;
    }
    char inodes[inodes_size][512];
    rewind(fp1);

    int fd_hlinks;
    char links_path[1024];
    strcpy(links_path, argv[1]);
    if ((strcmp(argv[1] + strlen(argv[1]) - 1, "/")) == 0)
        strcat(links_path, "hlinks.txt");
    else
        strcat(links_path, "/hlinks.txt");

    fd_hlinks = open(links_path, O_CREAT | O_WRONLY | O_TRUNC, 0600);
    if (fd_hlinks == -1) {
        fprintf(stderr, "Failed to open file '%s' (%d %s)\n", links_path, errno, strerror(errno));
        exit(11);
    }

    while ((fgets(line1, MAX_LENGTH, fp1)) != NULL) {
        files[0].date = strtok(line1, ",");
        files[0].path = strtok(NULL, ",");
        files[0].name = strtok(NULL, ",");
        files[0].size = strtok(NULL, ",");
        files[0].permissions = strtok(NULL, ",");
        files[0].inode = strtok(NULL, ",");
        printf("Comparing %s (%s) to:\n", files[0].path, files[0].inode);
        while ((fgets(line2, MAX_LENGTH, fp2)) != NULL) {
            files[1].date = strtok(line2, ",");
            files[1].path = strtok(NULL, ",");
            files[1].name = strtok(NULL, ",");
            files[1].size = strtok(NULL, ",");
            files[1].permissions = strtok(NULL, ",");
            files[1].inode = strtok(NULL, ",");
            printf("%s (%s)\n", files[1].path, files[1].inode);

            int potentially_equal = 1;
            int i = 0;
            for (; i < inodes_index; i++) {
                if (((strcmp(files[0].inode, inodes[i])) == 0) || ((strcmp(files[0].inode, inodes[i])) == 0))
                    potentially_equal = 0;
            }

            if ((strcmp(files[0].inode, files[1].inode)) == 0)
                potentially_equal = 0;

            if (((strcmp(files[0].name, files[1].name)) != 0) || ((strcmp(files[0].name, files[1].name)) != 0) || ((strcmp(files[0].name, files[1].name)) != 0))
                potentially_equal = 0;

            if (potentially_equal) {
                printf("%s is potentially_equal to %s\n", files[0].path, files[1].path);

                FILE *files0, *files1;
                files0 = fopen(files[0].path, "r");
                if (files0 == NULL) {
                    fprintf(stderr, "Failed to open file %s (%d %s)\n", files[0].path, errno, strerror(errno));
                    exit(12);
                }
                files1 = fopen(files[1].path, "r");
                if (files1 == NULL) {
                    fprintf(stderr, "Failed to open file %s (%d %s)\n", files[1].path, errno, strerror(errno));
                    exit(13);
                }

                char ch0, ch1;
                ch0 = getc(files0);
                ch1 = getc(files1);
                while ((ch0 != EOF) && (ch1 != EOF) && (ch0 == ch1)) {
                    ch0 = getc(files0);
                    ch1 = getc(files1);
                }

                if (ch0 == ch1) {
                    printf("%s is equal to %s\n", files[0].path, files[1].path);
                    // falta verificar erros
                    if ((remove(files[1].path)) != 0) {
                        fprintf(stderr, "Failed to remove %s (%d %s)\n", files[1].path, errno, strerror(errno));
                        exit(14);
                    }
                    if ((link(files[0].path, files[1].path)) != 0) {
                        fprintf(stderr, "Failed to hard-link files (%d %s)\n", errno, strerror(errno));
                        exit(15);
                    }
                    char link_str[1024];
                    strcpy(link_str, files[0].path);
                    strcat(link_str, " linked to ");
                    strcat(link_str, files[1].path);
                    strcat(link_str, "\n");
                    write(fd_hlinks, link_str, strlen(link_str));

                    strcpy(inodes[inodes_index], files[1].inode);
                    inodes_index++;
                }
                else {
                    printf("%s is different from %s\n",  files[0].path, files[1].path);
                }

                if ((fclose(files0)) != 0) {
                    fprintf(stderr, "Failed to close file %s (%d %s)\n", files[0].path, errno, strerror(errno));
                    exit(16);
                }
                if ((fclose(files1)) != 0) {
                    fprintf(stderr, "Failed to close file %s (%d %s)\n", files[1].path, errno, strerror(errno));
                    exit(17);
                }
            }

        }
        fseek(fp2, ftell(fp1), SEEK_SET);
        printf("\n");
    }

    if ((fclose(fp1)) != 0) {
        fprintf(stderr, "Failed to close file %s (%d %s)\n", dest_path, errno, strerror(errno));
        exit(18);
    }
    if ((fclose(fp2)) != 0) {
        fprintf(stderr, "Failed to close file %s (%d %s)\n", dest_path, errno, strerror(errno));
        exit(19);
    }
    if ((close(fd_hlinks)) != 0) {
        fprintf(stderr, "Failed to close file descriptor (%d %s)", errno, strerror(errno));
        exit(20);
    }

    printf("exiting...\n");
    return 0;
}
