# Assignment 4 – Introduction to MPI

**Course:** UCS645 – Parallel & Distributed Computing  
**Topic:** Message Passing Interface (MPI)  
**Processes Used:** 4  

---

## Objective

The objective of this assignment is to understand the fundamentals of **MPI (Message Passing Interface)** and implement basic parallel programs using multiple processes.

The assignment demonstrates:

- Point-to-point communication
- Collective communication
- Data distribution using `MPI_Scatter`
- Data aggregation using `MPI_Reduce`
- Parallel computation techniques

---

# Exercise 1: Ring Communication

## Problem Statement

- Process 0 initializes value **100**
- Each process adds its **rank**
- Value travels in a **ring topology**
- Final value returns to Process 0

## MPI Concepts Used

- `MPI_Send`
- `MPI_Recv`
- Process ranks
- Modulo operator for ring topology

## Execution Output (4 Processes)
Process 0 starts with value: 100
Process 1 updated value to: 101
Process 2 updated value to: 103
Process 3 updated value to: 106

Process 0 received final value: 106


## Explanation

Final value:

100 + (1 + 2 + 3) = 106

This confirms correct circular communication among processes.

---

# Exercise 2: Parallel Array Sum

## Problem Statement

- Create array from **1 to 100**
- Distribute using `MPI_Scatter`
- Each process computes local sum
- Combine using `MPI_Reduce`
- Expected result = **5050**

## MPI Concepts Used

- `MPI_Scatter`
- `MPI_Reduce`
- Parallel workload distribution

## Execution Output
Global Sum = 5050
Average = 50.5


## Verification

Sum formula:

n(n+1) / 2

100 × 101 / 2 = 5050

Average:

5050 / 100 = 50.5

Result matches expected value.

---

# Exercise 3: Global Maximum & Minimum

## Problem Statement

- Each process generates 10 random numbers (0–1000)
- Compute local maximum & minimum
- Use `MPI_MAXLOC` and `MPI_MINLOC`
- Identify process containing global values

## MPI Concepts Used

- `MPI_Reduce`
- `MPI_MAXLOC`
- `MPI_MINLOC`
- Struct-based reduction

## Sample Execution Output
Process 3 Local Max: 975 Local Min: 56
Process 0 Local Max: 863 Local Min: 21
Process 1 Local Max: 968 Local Min: 17
Process 2 Local Max: 944 Local Min: 89

Global Maximum: 975 (Process 3)
Global Minimum: 17 (Process 1)


## Observation

Results vary due to random number generation.  
Correct identification of both value and process confirms proper use of location-based reduction.

---

# Exercise 4: Parallel Dot Product

## Problem Statement

Compute dot product of:

A = [1,2,3,4,5,6,7,8]  
B = [8,7,6,5,4,3,2,1]

Expected Result:

120

## MPI Concepts Used

- `MPI_Scatter`
- Local computation
- `MPI_Reduce (MPI_SUM)`

## Execution Output
Dot Product = 120


## Verification

1×8 + 2×7 + 3×6 + 4×5 + 5×4 + 6×3 + 7×2 + 8×1 = 120

Correct output verifies accurate parallel computation.

---

# Performance Metrics

## Speedup

S = T₁ / Tₚ

Where:
- T₁ = Execution time with 1 process
- Tₚ = Execution time with p processes

## Efficiency

E = S / p

Efficiency indicates how effectively parallel resources are utilized.

---

# Overall Observations

- MPI enables efficient parallel computation.
- Communication overhead is minimal for small datasets.
- Scatter and Reduce simplify parallel data handling.
- Performance improvement depends on workload size and number of processes.

---

# Conclusion

This assignment successfully demonstrated:

- Process communication
- Data distribution
- Collective operations
- Parallel computation using MPI

All programs executed correctly using 4 processes and produced expected results.