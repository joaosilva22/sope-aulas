#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void sigint_handler(int signo) {
	printf("In SIGINT handler ...\n");
}

int main(void) {
	// int sigaction(int signum, const struct sigaction *act, struct sigation *oldact)
	// the sigaction() system call is used to change the action taken by a process on receipt of a specific signal
	// signum specifies the signal and can be any valid signal except SIGKILL and SIGSTOP
	// If act is non-NULL, the new action for signal signum is installed from act
	// If oldact is non-NULL, the previous action is saved in oldact
	// the sigaction struct has at least the following members :
	// struct sigaction {
	//     void (*sa_handler) (int); endereço do handler ou SIG_IGN ou SIG_DFL
	//     sigset_t sa_mask; sinais a acrescentar à mascara
	//     int sa_flags; modificam a ação do sinal
	// };

	// esta funcao subsitui signal() das primeiras versoes de Unix
	// os sinais especificados em sa_mask sao acrescentados à mascara antes de o handler ser invocado
	// quando o handler retornar a máscara é reposta no estado anterior
	// desta forma é possivel bloquear certos sinais durante a execução do handler
	// o sinal recebido é acrescentado automaticamente à mascara, garantindo que outras ocorrências do sinal serão bloqueadas até ao processamento da actual ocorrência ter terminado
	struct sigaction action;
	action.sa_handler = sigint_handler;
	// int sigemptyset(sigset_t *set)
	// sigemptyset() initializes the signal set given by set to empty, with all signals excluded from the set
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
	sigaction(SIGINT, &action, NULL);

	printf("Sleeping for 30 seconds ...\n");
	int sleepTime = 30;
	while(sleepTime > 0) {
		sleepTime = sleep(sleepTime);
		printf("sleeping for %d more seconds ...\n", sleepTime); 
	}
	printf("Waking up ...\n");
	exit(0);
}
