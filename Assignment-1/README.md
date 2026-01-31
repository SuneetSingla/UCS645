ASSIGNMENT 1 – REPORT
Github repo link : https://github.com/SuneetSingla/UCS645/tree/main

1. DAXPY Operation : operation using large arrays. 
size of array = 100000000

Threads	Time (s)
OMP_NUM_THREADS = 1	0.069902
OMP_NUM_THREADS = 2	0.066806
OMP_NUM_THREADS = 4	0.065876
OMP_NUM_THREADS = 8	0.094965

Observation : Execution time increases when threads exceed the number of available CPU cores.

2.	Matrix Multiply : [500x500] matrix 
2.1 – 1D Matrix : Parallelize outer loop
2.2	– 2D Matrix : parallelize nested loops 
Threads	            Time(1d)(s)	Time(2d)(s)
OMP_NUM_THREADS = 1	0.397639	0.383221
OMP_NUM_THREADS = 2	0.229863	0.303703
OMP_NUM_THREADS = 4	0.119622	0.190670
OMP_NUM_THREADS = 8	0.123581	0.106580

Observation : 2D is better for smaller thread counts. More threads can lead to overhead. 

3.	Pi calculation using integrals

Threads	Pi value 	Time (s)
OMP_NUM_THREADS = 1	3.1415926536	0.003538
OMP_NUM_THREADS = 2	3.1415926536	0.001922
OMP_NUM_THREADS = 4	3.1415926536	0.001288
OMP_NUM_THREADS = 8	3.1415926536	0.001016

Observation : Value is same every time and time decreases when threads increases
