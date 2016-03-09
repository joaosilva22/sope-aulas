#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

// compila o programa passado como argumento
// exemplo : ./p7c <nome-programa>

int main(int argc, char *argv[]) {
	char prog[20];

	sprintf(prog, "%s.c", argv[1]);
	// int execlp(const char *file, const char *arg, ...)
	// exec() : executes a file
	execlp("gcc", "gcc", prog, "-Wall", "-o", argv[1], NULL);
	printf("failed to compile %s\n", argv[1]);
	exit(1);
}
