# LAB 6 – CUDA Programming Assignment
## Name: Suneet Singla  
## Subject: UCS645 (Parallel Computing Lab)

---

## 🔹 Aim
The aim of this lab is to understand GPU programming using CUDA and analyze device properties, memory hierarchy, and parallel computation using CUDA kernels.

---

## 🔹 Software and Tools Used
- Ubuntu (WSL / Linux)
- VS Code
- NVIDIA CUDA Toolkit
- nvcc Compiler
- C/C++ Programming Language

---

## 🔹 How to Compile and Run Programs

    nvcc filename.cu -o filename
    ./filename

---

# 🔹 Part A: CUDA Device Query

## 🔸 Problem
Write a CUDA program to query GPU properties and analyze device characteristics.

## 🔸 Approach
- Used `cudaGetDeviceProperties()`
- Extracted GPU details like compute capability, memory, warp size, etc.
- Printed all device specifications

## 🔸 Output (Your System)

    Architecture: Ampere
    Compute Capability: 8.6
    Max Block Dimensions: (1024, 1024, 64)
    Max Threads (1D Grid): 65535 × 512 = 33,553,920
    Global Memory: 6143 MB
    Shared Memory: 48 KB
    Constant Memory: 64 KB
    Warp Size: 32

---

## 🔸 Answers

### 1. Architecture & Compute Capability
Ampere architecture with compute capability 8.6.

### 2. Maximum Block Dimensions
(1024, 1024, 64)

### 3. Maximum Threads (1D Configuration)
65535 × 512 = 33,553,920 threads

### 4. Why Not Always Use Maximum Threads?
- Limited shared memory and registers  
- Thread divergence  
- Memory bandwidth limitations  
- Kernel overhead  

### 5. What Limits Maximum Threads?
- GPU memory  
- Register usage  
- Shared memory per block  
- Hardware limits  

### 6. Shared Memory
Fast on-chip memory shared by threads. Available: 48 KB.

### 7. Global Memory
Large but slower memory. Available: 6143 MB (~6 GB).

### 8. Constant Memory
Read-only cached memory. Available: 64 KB.

### 9. Warp Size
Number of threads executed together. Warp size = 32.

### 10. Double Precision Support
Yes, supported.

---

# 🔹 Part B: Array Summation using CUDA

## 🔸 Problem
Calculate the sum of elements in a floating-point array using CUDA.

## 🔸 Approach
1. Allocate device memory using `cudaMalloc`  
2. Copy data from host to device  
3. Define grid and block dimensions  
4. Launch CUDA kernel  
5. Copy result back to host  
6. Free device memory  

## 🔸 Output

    Sum: 1000

## 🔸 Conclusion
Parallel execution improves performance for array summation.

---

# 🔹 Part C: Matrix Addition using CUDA

## 🔸 Problem
Perform addition of two large matrices using CUDA.

## 🔸 Approach
- Used 2D grid and block structure  
- Each thread computes one element  
- Performed element-wise addition in parallel  

## 🔸 Output

    Matrix Addition Success!

---

## 🔸 Analysis

### 1. Floating Operations
N² (one addition per element)

### 2. Global Memory Reads
2 × N² (reading from matrices A and B)

### 3. Global Memory Writes
N² (writing to matrix C)

---

## 🔹 Concepts Learned
- CUDA programming fundamentals  
- GPU architecture (Ampere)  
- Thread and block hierarchy  
- Memory types: global, shared, constant  
- Kernel execution  
- Parallel computation  

---

## 🔹 Result
All programs were successfully compiled and executed.

---

## 🔹 Final Conclusion
CUDA enables massive parallel execution on GPUs. Efficient use of memory and threads leads to faster computation for large-scale problems like array summation and matrix operations.

