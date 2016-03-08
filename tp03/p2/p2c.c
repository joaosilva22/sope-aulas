#include <unistd.h>
#include <stdio.h>

int main(void) {
	// printf("1") copies "1" into the buffer for standard output
	// because there is no newline at the end and the output is running in line-buffered mode [1], nothing appears on the terminal
	printf("1");
	if (fork() > 0) {
		// code executed by the parent
		// printf("2") and printf("3") copies "23" to the ouput buffer
		// the output buffer already contains "1" so after the printf calls it contains "123" but still no newline
		// because there is still no newline, nothing appears on the terminal
		printf("2");
		printf("3");
	} else {
		// code executed by the child
		// same as the parent, but in this process the standard output buffer has "145", and no newline
		printf("4");
		printf("5");
	}
	// finally copies the newline to the standard output buffer, writing on the terminal
	// parent's output buffer : "123\n"
	// child's output buffer : "145\n"
	// resulting in the following output :
	// 123
	// 145
	printf("\n");
	return 0;
}
// [1] line buffered mode : the output buffer is flushed only when the newline character is found (?)
