#include <stdio.h>
#include <stdlib.h>
// argc -> numero de argumentos da linha de comandos
// argv -> apontadores para as strings passadas como argumentos da linha de comandos
int main (int argc, char *argv[]) {
	int count = atoi(argv[argc - 1]);
	for (; count > 0; count--) {
		printf("Hello");
		int i = 1;
		for (; i < argc - 1; i++)
			printf(" %s", argv[i]);
		printf("!\n");
	}
	return 0;
}
