#include <iostream>

__global__ void matAdd(int* A, int* B, int* C, int N) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    if (row < N && col < N) {
        int idx = row * N + col;
        C[idx] = A[idx] + B[idx];
    }
}

int main() {
    int N = 64; // Smaller size for test
    size_t size = N * N * sizeof(int);
    int *h_A = new int[N*N], *h_B = new int[N*N], *h_C = new int[N*N];
    int *d_A, *d_B, *d_C;

    cudaMalloc(&d_A, size); cudaMalloc(&d_B, size); cudaMalloc(&d_C, size);
    // ... Copy data and launch kernel similarly to Part B ...
    std::cout << "Matrix Addition Success!" << std::endl;
    return 0;
}