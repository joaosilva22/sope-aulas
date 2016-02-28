#include <stdio.h>
#include <stdlib.h>
// o comando export no terminal cria uma variavel de ambiente
// p.ex. export USER_NAME=joaopsilva
int main(void) {
	printf("Hello %s!\n", getenv("USER_NAME"));
	return 0;
}
