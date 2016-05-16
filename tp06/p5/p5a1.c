#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    double a, b;
} args;

void *thr_add(void *arg) {
    double *ret;
    args *vals;

    ret = (double *) malloc(sizeof(double));
    vals = (args *) arg;
    *ret = vals->a + vals->b;
    return (void *) ret;
}

void *thr_sub(void *arg) {
    double *ret;
    args *vals;

    ret = (double *) malloc(sizeof(double));
    vals = (args *) arg;
    *ret = vals->a - vals->b;
    return (void *) ret;
}

void *thr_mul(void *arg) {
    double *ret;
    args *vals;

    ret = (double *) malloc(sizeof(double));
    vals = (args *) arg;
    *ret = vals->a * vals->b;
    return (void *) ret;
}

void *thr_div(void *arg) {
    double *ret;
    args *vals;

    ret = (double *) malloc(sizeof(double));
    vals = (args *) arg;
    *ret = vals->a / vals->b;
    return (void *) ret;
}

int main(int argc, char *argv[]) {
    args vals;
    pthread_t t_add, t_sub, t_mul, t_div;
    double res[4];

    if (argc != 3) {
        printf("Usage: %s <num_1> <num_2>\n", argv[0]);
        return 1;
    }

    vals.a = atof(argv[1]);
    vals.b = atof(argv[2]);

    pthread_create(&t_add, NULL, thr_add, (void *) &vals);
    pthread_create(&t_sub, NULL, thr_sub, (void *) &vals);
    pthread_create(&t_mul, NULL, thr_mul, (void *) &vals);
    pthread_create(&t_div, NULL, thr_div, (void *) &vals);

    pthread_join(t_add, (void**) &res[0]);
    printf("%.2f + %.2f = %.2f\n", vals.a, vals.b, res[0]);
    pthread_join(t_sub, (void**) &res[1]);
    printf("%.2f - %.2f = %.2f\n", vals.a, vals.b, res[1]);
    pthread_join(t_mul, (void**) &res[2]);
    printf("%.2f * %.2f = %.2f\n", vals.a, vals.b, res[2]);
    pthread_join(t_div, (void**) &res[3]);
    printf("%.2f / %.2f = %.2f\n", vals.a, vals.b, res[3]);

    return 0;
}
