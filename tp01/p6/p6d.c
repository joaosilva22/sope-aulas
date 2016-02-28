#include <stdio.h>
#include <stdlib.h>
#include <errno.h> // para poder utilizar errno em strerror
#include <string.h> // para utilizar strerror
// strerror devolve uma string correspondente ao erro indicado
// perror faz print do erro

#define BUF_LENGTH 256

int main(void) {
	FILE *src, *dst;
	char buf[BUF_LENGTH];

	if ((src = fopen("infile.txt", "r")) == NULL) {
		//printf("Error opening infile.txt: %s\n", strerror(errno));
		perror("Error opening infile.txt");
		exit(1);
	}

	if ((dst = fopen("outfile.txt", "w")) == NULL) {
		//printf("Error opening outfile.txt: %s\n", strerror(errno));
		perror("Error opening outfile.txt");
		exit(2);
	}

	while ((fgets(buf, BUF_LENGTH, src)) != NULL) {
		fputs(buf, dst);
	}
	fclose(src);
	fclose(dst);
	exit(0);
}
