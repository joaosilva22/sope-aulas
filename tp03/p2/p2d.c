#include <unistd.h>
#include <stdio.h>

int main(void) {
	// by addind the \n to printf() we flush the standard output buffer before fork()
	// meaning 1 is printed to the terminal
	printf("1\n");
	if (fork() > 0) {
		// code executed by the parent
		// the std output buffer is clean
		// 2 and 3 are copied to the output buffer, but not yet written to the terminal
		printf("2");
		printf("3");
	} else {
		// code executed by the child
		// the std output buffer is clean
		// 4 and 5 are copied to the output buffer, but not yet written to the terminal
		printf("4");
		printf("5");
	}
	// the output buffer is flushed
	// output :
	// 1 (std out buf : "1\n")
	// 23 (std out buf : "23\n")
	// 45 (std out buf : "45\n")
	printf("\n");
	return 0;
}
