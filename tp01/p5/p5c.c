#include <stdio.h>
#include <stdlib.h>
// getenv -> retorna variavel de ambiente com o nome especificado
int main(void) {
	printf("Hello %s!\n", getenv("USER"));
	return 0;
}
