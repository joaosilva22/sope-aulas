#include <stdio.h>
// argc -> numero de argumentos da linha de comandos
// argv -> apontadores para as strings passadas como argumentos da linha de comandos
int main (int argc, char *argv[]) {
	printf("Hello");
	int i = 1, count = argv[argc - 1];
	for (; i < argc; i++)
		printf(" %s", argv[i]);
	printf("!\n");
	return 0;
}
