#include <stdio.h>
// envp guarda apontadores para as variáveis de ambiente
int main(int argc, char* argv[], char* envp[]) {
	int i = 0;
	while (envp[i] != NULL) {
		printf("%s\n", envp[i]);
		i++;
	}
	return 0;
}
