#include <iostream>
#include <cstdlib>
#include <chrono>
#include "correlate.h"

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cout << "Usage: ./correlate_program ny nx\n";
        return 1;
    }

    int ny = atoi(argv[1]);
    int nx = atoi(argv[2]);

    float* data = new float[ny * nx];
    float* result = new float[ny * ny];

    // Initialize random matrix
    for (int i = 0; i < ny * nx; i++)
        data[i] = static_cast<float>(rand()) / RAND_MAX;

    auto start = std::chrono::high_resolution_clock::now();

    correlate(ny, nx, data, result);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Execution Time: "
              << elapsed.count() << " seconds\n";

    delete[] data;
    delete[] result;

    return 0;
}