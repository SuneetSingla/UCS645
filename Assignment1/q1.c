#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    int i;
    long N = 100000000;
    double a = 2.0;

    double *X = (double*) malloc(N * sizeof(double));
    double *Y = (double*) malloc(N * sizeof(double));
    for (i = 0; i < N; i++) {
        X[i] = 1.0;
        Y[i] = 2.0;
    }

    double start_parallel, end_parallel;

    start_parallel = omp_get_wtime();
    #pragma omp parallel for
    for (i = 0; i < N; i++) {
        X[i] = a * X[i] + Y[i];
    }
    end_parallel = omp_get_wtime();

    printf("Parallel Time : %f sec\n", end_parallel - start_parallel);

    free(X);
    free(Y);
    return 0;
}
