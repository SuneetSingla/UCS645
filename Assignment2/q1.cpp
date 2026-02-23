#include <iostream>
#include <vector>
#include <cmath>
#include <omp.h>
using namespace std;

struct Particle {
    double x, y, z;
    double fx, fy, fz;
};

void initialize_particles(vector<Particle>& p) {
    for (auto &pt : p) {
        pt.x = drand48();
        pt.y = drand48();
        pt.z = drand48();
        pt.fx = pt.fy = pt.fz = 0.0;
    }
}

double compute_forces_parallel(vector<Particle>& p) {
    int N = p.size();
    double energy = 0.0;

    vector<double> fx(N,0), fy(N,0), fz(N,0);

    #pragma omp parallel
    {
        vector<double> fx_local(N,0), fy_local(N,0), fz_local(N,0);

        #pragma omp for schedule(dynamic,10) reduction(+:energy)
        for (int i = 0; i < N; i++) {
            for (int j = i+1; j < N; j++) {

                double dx = p[i].x - p[j].x;
                double dy = p[i].y - p[j].y;
                double dz = p[i].z - p[j].z;

                double r2 = dx*dx + dy*dy + dz*dz;
                double inv_r2 = 1.0 / r2;
                double inv_r6 = inv_r2 * inv_r2 * inv_r2;

                double f = 24 * inv_r2 * inv_r6 * (2*inv_r6 - 1);

                fx_local[i] += f * dx;
                fy_local[i] += f * dy;
                fz_local[i] += f * dz;

                fx_local[j] -= f * dx;
                fy_local[j] -= f * dy;
                fz_local[j] -= f * dz;

                energy += 4 * inv_r6 * (inv_r6 - 1);
            }
        }

        #pragma omp critical
        {
            for(int i=0;i<N;i++){
                fx[i]+=fx_local[i];
                fy[i]+=fy_local[i];
                fz[i]+=fz_local[i];
            }
        }
    }

    for(int i=0;i<N;i++){
        p[i].fx = fx[i];
        p[i].fy = fy[i];
        p[i].fz = fz[i];
    }

    return energy;
}

int main() {
    int N = 2000;  
    vector<Particle> particles(N);

    initialize_particles(particles);

    double start = omp_get_wtime();
    double energy = compute_forces_parallel(particles);
    double end = omp_get_wtime();

    cout << "Total Energy: " << energy << endl;
    cout << "Execution Time: " << end - start << " seconds\n";

    return 0;
}
