#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BUF_LENGTH 256

int main(int argc, char* argv[]) {
	FILE *src, *dst;
	char buf[BUF_LENGTH];
	clock_t t1, t2;

	if (argc != 3) {
		printf("usage : %s <source> <destination>", argv[0]);
		exit(1);
	}

	if ((src = fopen(argv[1], "r")) == NULL) {
		printf("error : failed to open file %s\n", argv[1]);
		exit(2);
	}

	if ((dst = fopen(argv[2], "w")) == NULL) {
		printf("error: failed to open file %s\n", argv[2]);
		exit(3);
	}

	t1 = clock();

	while ((fgets(buf, BUF_LENGTH, src)) != NULL) {
		fputs(buf, dst);
	}
	fclose(src);cd ..
	fclose(dst);

	t2 = clock();
	printf("elapsed time : %.5f s\n", (double)(t2-t1)/CLOCKS_PER_SEC);

	return 0;
}
