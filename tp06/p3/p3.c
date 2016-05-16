#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 10

void *printHello(void *threadnum) {
    printf("Hello from thread no. %d!\n", *(int *) threadnum);
    pthread_exit(NULL);
}

int main(void) {
    pthread_t threads[NUM_THREADS];
    int t;

    for(t = 0; t < NUM_THREADS; t++) {
        printf("Creating thread %d\n", t);
        pthread_create(&threads[t], NULL, printHello, (void *) &t);
        pthread_join(threads[t], NULL);
    }
    pthread_exit(0);
}
