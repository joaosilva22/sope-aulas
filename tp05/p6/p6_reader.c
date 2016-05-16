#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int readline(int fd, char *str);

int main(void) {
    int fd;
    char str[100];

    // int mkfifo(const char *pathname, mode_t mode)
    // mkfifo() makes a FIFO special file with name pathname
    // mode specifies the FIFO's permissions
    // a FIFO special file is similar to a pipe, except that it is created in a different way.
    // once you have created a FIFO special file in this way, any process can open it for reading or writing, in the same way as an ordinary file.
    // however t must be open simultaneously at both ends before you can proceed to do any input or output operations on it
    mkfifo("/tmp/myfifo", 0660);
    fd = open("/tmp/myfifo", O_RDONLY);
    while (readline(fd, str))
        printf("%s", str);
    close(fd);
    return 0;
}

int readline(int fd, char *str) {
    int n;
    do {
        n = read(fd, str, 1);
    } while (n > 0 && *str++ != '\0');
    return (n > 0);
}
