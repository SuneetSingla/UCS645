#include <stdio.h>
#include <omp.h>

int main() {
    long i;
    long num_steps = 1000000;  
    double step;
    double x, sum = 0.0, pi;

    step = 1.0 / (double) num_steps;

    double start = omp_get_wtime();

    #pragma omp parallel for private(x) reduction(+:sum)
    for (i = 0; i < num_steps; i++) {
        x = (i + 0.5) * step;
        sum = sum + 4.0 / (1.0 + x * x);
    }

    pi = step * sum;

    double end = omp_get_wtime();

    printf("Calculated value of PI = %f\n", pi);
    printf("Execution Time = %f seconds\n", end - start);

    return 0;
}
