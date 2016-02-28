#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define BUF_LENGTH 256

int main(int argc, char* argv[]) {
	FILE *src, *dst;
	char buf[BUF_LENGTH];

	if ((src = fopen(argv[1], "r")) == NULL) {
		printf("Error opening file %s: %s\n", argv[1], strerror(errno));
		exit(1);
	}

	if ((dst = fopen(argv[2], "w")) == NULL) {
		printf("Error opening file %s: %s\n", argv[2], strerror(errno));
		exit(2);
	}

	while ((fgets(buf, BUF_LENGTH, src)) != NULL) {
		fputs(buf, dst);
	}
	fclose(src);
	fclose(dst);
	exit(0);
}
