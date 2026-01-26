#include <stdio.h>
#include <omp.h>

#define N 500   

int main() {
    int i, j, k;
    double A[N][N], B[N][N], C[N][N];

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            A[i][j] = 1.0;
            B[i][j] = 2.0;
            C[i][j] = 0.0;
        }
    }

    double start = omp_get_wtime();

    #pragma omp parallel for
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            for (k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    double end = omp_get_wtime();

    printf("1D Parallel Matrix Multiplication Time: %f seconds\n", end - start);

    return 0;
}
