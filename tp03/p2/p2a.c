#include <unistd.h>

int main(void) {
	// write() writes directly to the terminal
	// meaning that the strings are written immediatly after the call
	write(STDOUT_FILENO, "1", 1);
	if (fork() > 0) {
		// code executed by the parent
		write(STDOUT_FILENO, "2", 1);
		write(STDOUT_FILENO, "3", 1);
	} else {
		// code executed by the child
		write(STDOUT_FILENO, "4", 1);
		write(STDOUT_FILENO, "5", 1);
	}
	write(STDOUT_FILENO, "\n", 1);
	return 0;
	// output :
	// 123 (código executado pelo parent, seguido de newline)
	// 45 (código executado pelo child, seguido de newline)
}
