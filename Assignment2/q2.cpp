#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

static inline int score(char a, char b){ return (a==b) ? 2 : -1; }

int main(){
    string A = "ACACACTA";
    string B = "AGCACACA";
    int n = A.size(), m = B.size();
    int gap = -2;

    vector<int> H((n+1)*(m+1), 0);
    auto idx = [&](int i,int j){ return i*(m+1)+j; };

    double start = omp_get_wtime();

    for(int d=2; d<=n+m; d++){
        int iStart = max(1, d-m);
        int iEnd   = min(n, d-1);

        #pragma omp parallel for schedule(static)
        for(int i=iStart; i<=iEnd; i++){
            int j = d - i;

            int match = H[idx(i-1,j-1)] + score(A[i-1], B[j-1]);
            int del   = H[idx(i-1,j)] + gap;
            int ins   = H[idx(i,j-1)] + gap;

            H[idx(i,j)] = max(0, max(match, max(del, ins)));
        }
    }

    double end = omp_get_wtime();

    cout << "Smith-Waterman Alignment (OpenMP)\n";
    cout << "Execution Time: " << end - start << " seconds\n";

    return 0;
}