#include "metrics.h"
#include <algorithm>
#include <numeric>
#include <iostream>
#include <iomanip>
#include <fstream>

Metrics calculateMetrics(
    const std::vector<Task>& tasks,
    int num_processors,
    int sequential_time)
{
    Metrics m;

    // 1. MAKESPAN — find when the very last task finishes
    m.makespan = 0;
    for (const auto& t : tasks) {
        m.makespan = std::max(m.makespan, t.finish_time);
    }

    // 2. UTILIZATION — how busy was each processor?
    std::vector<int> busy_time(num_processors, 0);
    for (const auto& t : tasks) {
        busy_time[t.assigned_processor] += t.execution_time;
    }

    double total_util = 0.0;
    for (int b : busy_time) {
        total_util += (double)b / m.makespan;
    }
    m.avg_utilization = total_util / num_processors;

    // 3. LOAD IMBALANCE — how uneven is the workload?
    int max_busy = *std::max_element(busy_time.begin(), busy_time.end());
    int min_busy = *std::min_element(busy_time.begin(), busy_time.end());
    double avg_busy = std::accumulate(busy_time.begin(), busy_time.end(), 0.0) / num_processors;
    m.load_imbalance = (avg_busy > 0) ? (double)(max_busy - min_busy) / avg_busy : 0.0;

    // 4. SPEEDUP — how much faster than doing all tasks one by one?
    m.speedup = (double)sequential_time / m.makespan;

    return m;
}

void printMetrics(const std::string& algo_name, const Metrics& m) {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "┌─────────────────────────────────┐" << std::endl;
    std::cout << "│  Algorithm: " << std::left << std::setw(20) << algo_name << "│" << std::endl;
    std::cout << "├─────────────────────────────────┤" << std::endl;
    std::cout << "│  Makespan:       " << std::setw(8) << m.makespan       << " units   │" << std::endl;
    std::cout << "│  Utilization:    " << std::setw(7) << m.avg_utilization*100 << "%         │" << std::endl;
    std::cout << "│  Load Imbalance: " << std::setw(8) << m.load_imbalance << "          │" << std::endl;
    std::cout << "│  Speedup:        " << std::setw(7) << m.speedup        << "x         │" << std::endl;
    std::cout << "└─────────────────────────────────┘" << std::endl;
    std::cout << std::endl;
}

void saveToCSV(const std::string& algo, double makespan, double util, double imbalance, double speedup) {
    std::ofstream file;
    file.open("results.csv", std::ios::app);

    file << algo << "," 
         << makespan << "," 
         << util * 100 << ","   // convert to percentage
         << imbalance << "," 
         << speedup << "\n";

    file.close();
}