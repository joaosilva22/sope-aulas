#include <stdio.h>
#include <stdlib.h>

void handler1() {
	printf("Executing exit handler 1\n");
}

void handler2() {
	printf("Executing exit handler 2\n");
	// exit(1);
	// o exit muda o valor de retorno, mas o handlers executam na mesma
}

int main() {
	atexit(handler1);
	atexit(handler2);
	// os handlers sao executados na ordem inversa de instalacao
	// neste caso primeiro sera chamado o handler2
	// seguido do handler1
	// abort();
 	// abort causa Aborted (core dumped)
	// neste caso os exit handlers nao sao executados
	printf("Main done!\n");
	return 0;
}
