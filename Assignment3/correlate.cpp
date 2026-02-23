#include <vector>
#include <cmath>
#include <omp.h>
#include "correlate.h"

void correlate(int ny, int nx, const float* data, float* result)
{
    std::vector<double> mean(ny);
    std::vector<double> norm(ny);
    std::vector<double> normalized(ny * nx);

    // Compute mean of each row
#pragma omp parallel for
    for (int i = 0; i < ny; i++)
    {
        double sum = 0.0;
        for (int x = 0; x < nx; x++)
            sum += data[x + i * nx];

        mean[i] = sum / nx;
    }

    // Normalize rows
#pragma omp parallel for
    for (int i = 0; i < ny; i++)
    {
        double sq_sum = 0.0;

        for (int x = 0; x < nx; x++)
        {
            double val = data[x + i * nx] - mean[i];
            normalized[x + i * nx] = val;
            sq_sum += val * val;
        }

        norm[i] = sqrt(sq_sum);
    }

    // Compute correlations
#pragma omp parallel for schedule(static)
    for (int i = 0; i < ny; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            double dot = 0.0;

            for (int x = 0; x < nx; x++)
                dot += normalized[x + i * nx] *
                       normalized[x + j * nx];

            result[i + j * ny] =
                dot / (norm[i] * norm[j]);
        }
    }
}