#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define MAX 50000

int main(void) {
	int i;
	pid_t pid;
	char str[10];

	pid = fork();
	switch (pid) {
		case -1:
			perror("fork ");
			break;
		// child
		case 0: 
			for (i = 1; i <= MAX; i++) {
				// int sprintf(char *str, const char *format, ...)
				// sprintf() : writes to the character string str
				sprintf(str, "-%d", i);
				write(STDOUT_FILENO, str, strlen(str));
			}
			break;
		// parent
		default: 
			for (i = 1; i <= MAX; i++) {
				sprintf(str, "+%d", i);
				write(STDOUT_FILENO, str, strlen(str));
			}
	}
	return 0;
}
