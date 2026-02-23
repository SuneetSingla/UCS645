#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

int main() {
    int N = 500;
    int steps = 500; 
    double alpha = 0.1;

    vector<vector<double>> T(N, vector<double>(N, 25.0));
    vector<vector<double>> T_new(N, vector<double>(N, 25.0));

    T[N/2][N/2] = 100.0;

    double start = omp_get_wtime();

    for (int t = 0; t < steps; t++) {

        #pragma omp parallel for schedule(static)
        for (int i = 1; i < N-1; i++) {
            for (int j = 1; j < N-1; j++) {
                T_new[i][j] = T[i][j] + alpha * (
                    T[i+1][j] + T[i-1][j] +
                    T[i][j+1] + T[i][j-1] -
                    4*T[i][j]
                );
            }
        }


        T.swap(T_new);
    }

    double end = omp_get_wtime();

    cout << "Final center temp: " << T[N/2][N/2] << endl;
    cout << "Execution Time: " << end - start << " seconds\n";

    return 0;
}
