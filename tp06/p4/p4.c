#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *thr_func(void *arg) {
    int *ret;

    ret = (int *) malloc(sizeof(int));
    *ret = *(int *) arg;
    sleep(1);
    printf("I'm thread no. %d with tid=%lu\n", *(int *) arg, pthread_self());
    return (void *) ret;
}

int main(int argc, char *argv[]) {
    int nt;
    pthread_t *tids;
    int *values, k, *r;

    if (argc != 2) {
        printf("Usage: %s <n_threads>\n", argv[0]);
        return 1;
    }

    nt = atoi(argv[1]);
    if (nt < 1) {
        printf("Number of threads should be greater than 1!\n");
        return 1;
    }

    tids = (pthread_t *) malloc(nt * sizeof(pthread_t));
    values = (int *) malloc(nt * sizeof(int));

    for(k = 0; k < nt; k++) {
        values[k] = k;
        pthread_create(&(tids[k]), NULL, thr_func, &(values[k]));
    }

    for(k = 0; k < nt; k++) {
        pthread_join(tids[k], (void **) &r);
        printf("Thread %lu terminated with return = %d\n", tids[k], *r);
        free(r);
    }
    free(tids);
    free(values);
    return 0;
}
