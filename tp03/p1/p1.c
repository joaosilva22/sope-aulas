#include <unistd.h>
#include <stdio.h>

int global = 1;

int main(void) {
	int local = 2;
	// fork() : creates a new process by duplicating the calling process
	// the new process, referred to as the child, is an exact duplicate of the calling process, referred to as the parent
	// except for the  following points :
	// * the child has its own unique process ID, and this PID does not match the ID of any existing process group
	// * the child's parent process ID is the same as the parent's process ID
	// * ...
	// return value : on success, the PID of the child process is returned in the parent, and 0 is returned in the child
	// on failure, -1 is returned in the parent, and no child process is created
	if (fork() > 0) { // the 'parent'
		// getpid() : returns the process ID of the calling process
		// getppid() : returns the process ID of the parent of the calling process
		printf("PID = %d; PPID = %d\n", getpid(), getppid());
		global++;
		local--;
	} else { // the 'child'
		printf("PID = %d; PPID = %d\n", getpid(), getppid());
		global--;
		local++;
	}
	printf("PID = %d - global = %d ; local = %d\n", getpid(), global, local);
	return 0;
	// executando varias vezes o PID vai incrementando
	// o PID do parent process e sempre menor que o PID do child process
}
