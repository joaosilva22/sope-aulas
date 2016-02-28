#include <stdio.h>
#include <stdlib.h>
#include <time.h> // para poder utilizar time(NULL) em srand

int main(int argc, char* argv[]) {
	if (argc != 3) {
		printf("usage: %s range target\n", argv[0]);
		exit(1);
	}
	srand(time(NULL));
	int r = -1, i = 0;
	do {
		r = rand() % atoi(argv[1]);
		// rand % x dá um numero entre [0, x[
		printf("%d : %d\n", i, r);
		i++;
	} while (r != atoi(argv[2]));
	return 0;
}
