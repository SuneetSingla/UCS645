#include <iostream>
#include <cuda_runtime.h>

__global__ void sumKernel(float* d_arr, float* d_res, int n) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < n) {
        atomicAdd(d_res, d_arr[i]); // Simplest way to sum into one variable
    }
}

int main() {
    int n = 1000;
    size_t size = n * sizeof(float);
    float h_arr[1000];
    float h_res = 0;

    for(int i=0; i<n; i++) h_arr[i] = 1.0f; // Initialize array with 1s

    float *d_arr, *d_res;
    cudaMalloc(&d_arr, size);
    cudaMalloc(&d_res, sizeof(float));

    cudaMemcpy(d_arr, h_arr, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_res, &h_res, sizeof(float), cudaMemcpyHostToDevice);

    sumKernel<<<(n+255)/256, 256>>>(d_arr, d_res, n);

    cudaMemcpy(&h_res, d_res, sizeof(float), cudaMemcpyDeviceToHost);
    std::cout << "Sum: " << h_res << std::endl;

    cudaFree(d_arr); cudaFree(d_res);
    return 0;
}