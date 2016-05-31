#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// numero maximo de posicoes
#define MAXELEMS 10000000
// numero maximo de threads
#define MAXTHREADS 100
#define min(a, b) (a)<(b)?(a):(b)

int npos;
// mutex para seccao critica
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
// variaveis partilhadas
int buf[MAXELEMS], pos = 0, val = 0;

void *fill(void *nr) {
    while (1) {
        pthread_mutex_lock(&mut);
        if (pos >= npos) {
            pthread_mutex_unlock(&mut);
            return NULL;
        }
        buf[pos] = val;
        pos++; val++;
        pthread_mutex_unlock(&mut);
        *(int *) nr += 1;
    }
}

void *verify(void *arg) {
    int k;
    for (k = 0; k < npos; k++)
        if (buf[k] != k)
            printf("ERROR: buf[%d] = %d\n", k, buf[k]);
    return NULL;
}

int main(int argc, char *argv[]) {
    // array para contagens
    int k, nthr, count[MAXTHREADS];
    // tids dos threads
    pthread_t tidf[MAXTHREADS], tidv;
    int total;

    if (argc != 3) {
        printf("Usage: %s <nr_pos> <nr_thrs>\n", argv[0]);
        return 1;
    }

    // numero efetivo de posicoes
    npos = min(atoi(argv[1]), MAXELEMS);
    // numero efetico de threads
    nthr = min(atoi(argv[2]), MAXTHREADS);

    // criacao das threads 'fill'
    for (k = 0; k < nthr; k++) {
        count[k] = 0;
        pthread_create(&tidf[k], NULL, fill, &count[k]);
    }

    total = 0;
    // espera threads 'fill'
    for (k = 0; k < nthr; k++) {
        pthread_join(tidf[k], NULL);
        printf("count[%d] = %d\n", k, count[k]);
        total += count[k];
    }
    printf("total count = %d\n", total);

    pthread_create(&tidv, NULL, verify, NULL);
    pthread_join(tidv, NULL);

    return 0;
}
