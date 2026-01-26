// name - suneet singla 
// roll no - 102303615

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    int i;
    int N = 65536;         
    double a = 2.0;

    double X[N], Y[N];

    for (i = 0; i < N; i++) {
        X[i] = 1.0;
        Y[i] = 2.0;
    }

    double start, end;

    start = omp_get_wtime();

    #pragma omp parallel for
    for (i = 0; i < N; i++) {
        X[i] = a * X[i] + Y[i];
    }

    end = omp_get_wtime();

    printf("Time: %f sec", end - start);

    return 0;
}

