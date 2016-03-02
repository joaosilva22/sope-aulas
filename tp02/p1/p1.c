// the termios functions describe a general terminal interface that is 
// provided to control asynchronous communications ports
#include <termios.h>
#include <unistd.h>
#include <string.h>

#define MAX_PASSWD_LEN 20

int main(void) {
	// a struct termios tem pelo menos os sequintes membros :
	// tcflag_t c_iflag - input modes
	// tcflag_t c_oflag - output modes
	// tcflag_t c_cflag - control modes
	// tcflag_t c_lflag - local modes
	// cc_t     c_cc[NCCS] - special characters
	struct termios term, oldterm;
	int i;
	char pass[MAX_PASSWD_LEN+1], ch, echo = '*';

	// ssize_t write(int fd, const void *buf, size_t count)
	// write() writes up to count bytes from the buffer pointed buf to
	// the file referred to by the file descriptor fd
	// STDOUT_FILENO is defined in C programs as the file descriptor number for the stdout file stream
	write(STDOUT_FILENO, "Password? ", 11);

	// tcgetattr(int fd, struct termios *termios_p)
	// guarda as informacoes do fd na struct apontada por termios_p
	// STDIN_FILENO e o file descriptor para o stdin file stream
	tcgetattr(STDIN_FILENO, &oldterm);
	term = oldterm;
	// c_lflag (local modes) :
	// ICANON : enable canonical mode	
	// ECHO : echo input characters
	// ECHOE : if ICANON is also set, set the ERASE character erases the preceding input character, and WERASE erases the preceding word
	// ECHOK : if ICANON is also set, the KILL character erases the current line
	// ECHONL : if ICANON is also set, echo the NL character even if ECHO is not set
	term.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL | ICANON);
	// int tcsetattr(int fd, int optional_actions, const struct termios *termios_p)	
	// TCSAFLUSH : the change occurs after all output writen to the object referred by fd has been transmitted, and all input that has been received but not read will be discarded before the change is made
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);

	i=0;
	while(i < MAX_PASSWD_LEN && read(STDIN_FILENO, &ch, 1) && ch != '\n') {
		pass[i++] = ch;
		write(STDOUT_FILENO, &echo, 1);
	}
	// termina a string pass com '\0'
	pass[i] = 0;
	
	// repor as settings originais
	// TCSANOW : the change occurs immediately
	tcsetattr(STDIN_FILENO, TCSANOW, &oldterm);

	write(STDOUT_FILENO, "\nPassword: ", 12);
	write(STDOUT_FILENO, pass, strlen(pass));
	write(STDOUT_FILENO, "\n", 1);

	return 0;
}
