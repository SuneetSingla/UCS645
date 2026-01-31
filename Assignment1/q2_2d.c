#include <stdio.h>
#include <omp.h>

#define N 500

int main() {
    int i, j, k;
    static double A[N][N], B[N][N], C[N][N];

    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++) {
            A[i][j] = 1.0;
            B[i][j] = 2.0;
            C[i][j] = 0.0;
        }

    double start_parallel, end_parallel;
    start_parallel = omp_get_wtime();

    #pragma omp parallel for collapse(2) private(k)
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            for (k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    end_parallel = omp_get_wtime();
    double parallel_time = end_parallel - start_parallel;

    printf("Parallel Time (2D)     : %f sec\n", parallel_time);
    return 0;
}
