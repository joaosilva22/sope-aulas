#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// includes para medir o tempo:
#include <unistd.h> // permite usar sysconf()
#include <sys/times.h> // define a struct tms

int main(int argc, char* argv[]) {
	long tcks;
	clock_t t1, t2;
	struct tms clocks;
	if (argc != 3) {
		printf("usage: %s <max-rand> <nr-tomatch>\n", argv[0]);
		exit(1);
	}
	srand(time(NULL));
	// sysconf - get configuration information at run time
	// _SC_CLK_TCK - the number of clock ticks per second
	// tcks e o numero de ticks do clock por segundo
	tcks = sysconf(_SC_CLK_TCK);
	// times - get process times
	// clock_t times(struct tms *buf)
	// times stores the current process times in the struct tms that buf points to
	// the struct tms is defined in <sys/times.h>
	// struct tms {
	//     clock_t tms_utime; (user time)
	//     clock_t tms_stime; (system time)
	//     clock_t tms_cutime; (user time of children)
	//     clock_t tms_cstime; (system time of children)
	// };
	// returns the number of clock ticks that have elapsed since an arbitrary point in the past
	t1 = times(NULL);
	int r = -1, i = 0;
	do {
		r = rand() % atoi(argv[1]);
		printf("%d : %d\n", i, r);
		i++;
	} while (r != atoi(argv[2]));
	t2 = times(&clocks);
	// tempo real em segundos :
	// (t2 - t1) / tcks
	printf("elapsed time : %.3f s\n", (double)(t2-t1)/tcks);
	// tempo de CPU :
	// clocks.tms_[u/s]time / tcks
	printf("cpu user time : %.3f s\n", (double)clocks.tms_utime/tcks);
	printf("cpu system time : %.3f s\n", (double)clocks.tms_stime/tcks);
	return 0;
}
