#include <stdio.h>
#include <omp.h>

int main() {
    long i;
    long num_steps = 1000000;
    double step, x, sum, pi;

    step = 1.0 / (double) num_steps;

    double start_parallel, end_parallel;

    sum = 0.0;
    start_parallel = omp_get_wtime();

    #pragma omp parallel for private(x) reduction(+:sum)
    for (i = 0; i < num_steps; i++) {
        x = (i + 0.5) * step;
        sum += 4.0 / (1.0 + x * x);
    }

    pi = step * sum;
    end_parallel = omp_get_wtime();
    double parallel_time = end_parallel - start_parallel;

    printf("Calculated PI  : %.12f\n", pi);
    printf("Parallel Time  : %f sec\n", parallel_time);

    return 0;
}
