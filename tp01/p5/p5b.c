#include <stdio.h>
// envp guarda apontadores para as variáveis de ambiente
int main(int argc, char* argv[], char* envp[]) {
	int i = 0;
	while (envp[i] != NULL) {
		if (!strncmp(envp[i], "USER=", 5)) {
			printf("Hello %s!\n", envp[i] + 5);
		}
		i++;
	}
	return 0;
}
