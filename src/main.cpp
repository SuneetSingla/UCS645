#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <fstream>
#include "task.h"
#include "scheduler.h"
#include "metrics.h"

int main() {

    std::ofstream file("results.csv");
    file << "Algorithm,Makespan,Utilization,LoadImbalance,Speedup\n";
    file.close();

    std::vector<int> task_sizes = {50, 100, 200};
    std::vector<int> processors = {2, 4, 8};

    int max_exec_time = 50;

    std::vector<std::string> algorithms = {
        "FCFS",
        "RoundRobin",
        "MinMin",
        "MaxMin",
        "LoadAware"
    };

    for (int t : task_sizes) {
        for (int p : processors) {

            std::cout << "\n========================================" << std::endl;
            std::cout << "Tasks = " << t << " | Processors = " << p << std::endl;
            std::cout << "========================================\n" << std::endl;

            std::vector<Task> original_tasks = generateTasks(t, max_exec_time);

            int sequential_time = 0;
            for (const auto& task : original_tasks) {
                sequential_time += task.execution_time;
            }

            std::cout << "Sequential Time: " << sequential_time << "\n" << std::endl;

            for (const std::string& algo : algorithms) {

                std::vector<Task> tasks = original_tasks;

                tasks = schedule(tasks, p, algo);

                Metrics m = calculateMetrics(tasks, p, sequential_time);

                printMetrics(algo, m);

                saveToCSV(algo, m.makespan, m.avg_utilization, m.load_imbalance, m.speedup);
            }
        }
    }

    std::cout << "\nAll experiments completed. Results saved to results.csv\n";

    return 0;

}