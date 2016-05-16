#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *thr_add(void *arg) {
    double *op;
    op = (double *) arg;
    printf("%.2f + %.2f = %.2f\n", op[0], op[1], op[0] + op[1]);
    return NULL;
}

void *thr_sub(void *arg) {
    double *op;
    op = (double *) arg;
    printf("%.2f - %.2f = %.2f\n", op[0], op[1], op[0] - op[1]);
    return NULL;
}

void *thr_mul(void *arg) {
    double *op;
    op = (double *) arg;
    printf("%.2f * %.2f = %.2f\n", op[0], op[1], op[0] * op[1]);
    return NULL;
}

void *thr_div(void *arg) {
    double *op;
    op = (double *) arg;
    printf("%.2f / %.2f = %.2f\n", op[0], op[1], op[0] / op[1]);
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t t_add, t_sub, t_mul, t_div;
    double op[2];

    if (argc != 3) {
        printf("Usage: %s <num_1> <num_2>\n", argv[0]);
        return 1;
    }

    op[0] = atof(argv[1]);
    op[1] = atof(argv[2]);

    pthread_create(&t_add, NULL, thr_add, (void *) op);
    pthread_create(&t_sub, NULL, thr_sub, (void *) op);
    pthread_create(&t_mul, NULL, thr_mul, (void *) op);
    pthread_create(&t_div, NULL, thr_div, (void *) op);

    pthread_join(t_add, NULL);
    pthread_join(t_sub, NULL);
    pthread_join(t_mul, NULL);
    pthread_join(t_div, NULL);

    return 0;
}
