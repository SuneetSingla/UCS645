# Parallel Correlation Matrix Computation (OpenMP)

## Course
UCS645: Parallel & Distributed Computing  

## Objective

This assignment implements a parallel algorithm to compute the **Pearson correlation coefficient** between every pair of input vectors using C++ and OpenMP.

The program evaluates performance improvement using multithreading and analyzes scalability.

---

# Problem Statement

You are given:

- `ny` input vectors  
- Each vector contains `nx` floating point numbers  

The input matrix is stored in row-major format:

data[x + y * nx]

For all:

0 ≤ j ≤ i < ny

We compute:

correlation(row_i, row_j)

The result is stored in:

result[i + j * ny]

All arithmetic operations are performed using **double precision** to ensure numerical accuracy.

---

# Pearson Correlation Formula

The Pearson correlation coefficient between vectors A and B is:

corr(A,B) =  
( Σ (Aᵢ − μₐ)(Bᵢ − μᵦ) )  
--------------------------------------------  
√( Σ (Aᵢ − μₐ)² ) × √( Σ (Bᵢ − μᵦ)² )

Where:
- μₐ and μᵦ are the means of the respective vectors.

---

# Implementation Details

## 1️⃣ Sequential Baseline

The baseline implementation:

- Computes mean of each row
- Computes numerator and denominator
- Stores lower triangular correlation matrix
- Uses double precision arithmetic

---

## 2️⃣ Parallelization with OpenMP

Parallelization strategy:

- The outer loop over `i` is parallelized
- OpenMP directive used:

#pragma omp parallel for schedule(static)

Each thread independently computes correlations for different rows.

---

## 3️⃣ Optimizations Applied

To improve performance:

- Precomputed mean for each row
- Precomputed normalized rows
- Converted correlation computation into a dot product
- Used compiler optimizations:

-O3 -march=native -fopenmp

- Static scheduling to reduce runtime overhead

---

# File Structure

Makefile  
main.cpp  
correlate.cpp  
correlate.h  
README.md  

---

# Compilation

To compile:

make

This generates the executable:

correlate_program

---

# Execution

Run with:

OMP_NUM_THREADS=<threads> ./correlate_program <ny> <nx>

Example:

OMP_NUM_THREADS=4 ./correlate_program 2000 2000

---

# Performance Evaluation

Matrix size tested:

2000 × 2000

## Measured Execution Times

| Threads | Time (s) |
|----------|----------|
| 1 | 2.105 |
| 2 | 1.549 |
| 4 | 0.957 |
| 8 | 0.531 |

---

# Speedup Calculation

Speedup(p) = T(1) / T(p)

| Threads | Speedup |
|----------|----------|
| 1 | 1.00 |
| 2 | 1.36 |
| 4 | 2.20 |
| 8 | 3.96 |

---

# Efficiency Calculation

Efficiency = Speedup / Number_of_Threads

| Threads | Efficiency |
|----------|------------|
| 1 | 100% |
| 2 | 68% |
| 4 | 55% |
| 8 | 49% |

---

# Discussion

The results demonstrate:

- Significant performance improvement using multithreading
- Nearly 4× speedup with 8 threads
- Decreasing efficiency at higher thread counts due to:
  - Memory bandwidth limitations
  - Cache contention
  - Thread management overhead
  - Synchronization costs

The workload size (2000 × 2000) provides sufficient computation to benefit from parallel execution.

---

# Conclusion

The OpenMP-based parallel implementation significantly improves performance over the sequential baseline.

While ideal linear scaling is not achieved, the program demonstrates effective utilization of multicore CPU architecture and optimized memory access patterns.

Further improvements could include:

- SIMD vectorization
- Cache blocking
- NUMA-aware memory allocation
- Larger workload sizes

---

# Technologies Used

- C++
- OpenMP
- GNU Make
- GCC Compiler

---

# Clean Build Files

make clean

---
