#pragma once
#include "task.h"
#include <vector>
#include <string>

struct Metrics {
    int    makespan;          // total time from start to end
    double avg_utilization;   // average % time processors were busy
    double load_imbalance;    // how uneven the work distribution was
    double speedup;           // how much faster than sequential
};

Metrics calculateMetrics(
    const std::vector<Task>& tasks,
    int num_processors,
    int sequential_time
);

void printMetrics(const std::string& algo_name, const Metrics& m);

void saveToCSV(const std::string& algo, double makespan, double util, double imbalance, double speedup);

