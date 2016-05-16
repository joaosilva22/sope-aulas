#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define STDERR 2
#define NUMITER 10000

void * thrfunc(void * arg) {
    int i;

    fprintf(stderr, "Starting thread %s\n", (char *) arg);
    for (i = 1; i <= NUMITER; i++) write(STDERR, arg, 1);
    return NULL;
}

int main(void) {
    pthread_t ta, tb;
    int ta_arg = '1', tb_arg = '2';

    // int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg)
    // the pthread_create() function starts a new thread in the calling process. The new thread starts execution by invoking start_routine(); arg is passed as the sole argument of start_routine()
    pthread_create(&ta, NULL, thrfunc, &ta_arg);
    pthread_create(&tb, NULL, thrfunc, &tb_arg);

    pthread_join(ta, NULL);
    pthread_join(tb, NULL);

    return 0;
}
