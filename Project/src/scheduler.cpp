#include "scheduler.h"
#include <algorithm>
#include <omp.h>
#include <climits>

bool isReady(const Task& task, const std::vector<Task>& all_tasks) {
    for (int dep_id : task.dependencies) {
        if (all_tasks[dep_id].finish_time == -1) {
            return false; // a dependency is not done yet
        }
    }
    return true;
}

int getEarliestStart(const Task& task, const std::vector<Task>& all_tasks) {
    int earliest = 0;
    for (int dep_id : task.dependencies) {
        earliest = std::max(earliest, all_tasks[dep_id].finish_time);
    }
    return earliest;
}

int getLeastBusyProcessor(const std::vector<int>& processor_free_time) {
    int best = 0;
    for (int i = 1; i < (int)processor_free_time.size(); i++) {
        if (processor_free_time[i] < processor_free_time[best]) {
            best = i;
        }
    }
    return best;
}

std::vector<Task> schedule(
    std::vector<Task> tasks,
    int num_processors,
    const std::string& algorithm)
{
    int n = tasks.size();

    std::vector<int> processor_free_time(num_processors, 0);

    std::vector<bool> done(n, false);
    int completed = 0;
    int round_robin_counter = 0; 

    while (completed < n) {

        std::vector<int> ready_ids;
        for (int i = 0; i < n; i++) {
            if (!done[i] && tasks[i].start_time == -1 && isReady(tasks[i], tasks)) {
                ready_ids.push_back(i);
            }
        }

        if (ready_ids.empty()) break;

        if (algorithm == "FCFS") {
        }
        else if (algorithm == "RoundRobin") {
        }
        else if (algorithm == "MinMin") {
            std::sort(ready_ids.begin(), ready_ids.end(), [&](int a, int b) {
                return tasks[a].execution_time < tasks[b].execution_time;
            });
        }
        else if (algorithm == "MaxMin") {
            std::sort(ready_ids.begin(), ready_ids.end(), [&](int a, int b) {
                return tasks[a].execution_time > tasks[b].execution_time;
            });
        }
        else if (algorithm == "LoadAware") {
            std::sort(ready_ids.begin(), ready_ids.end(), [&](int a, int b) {
                return tasks[a].execution_time < tasks[b].execution_time;
            });
        }

        #pragma omp parallel for num_threads(num_processors) schedule(dynamic)
        for (int idx = 0; idx < (int)ready_ids.size(); idx++) {
            int task_id = ready_ids[idx];
            int proc = 0;

            #pragma omp critical
            {
                if (algorithm == "RoundRobin") {
                    proc = round_robin_counter % num_processors;
                    round_robin_counter++;
                }
                else if (algorithm == "LoadAware") {
                    proc = getLeastBusyProcessor(processor_free_time);
                }
                else {
                    proc = idx % num_processors;
                }

                int earliest = getEarliestStart(tasks[task_id], tasks);
                int actual_start = std::max(earliest, processor_free_time[proc]);

                tasks[task_id].assigned_processor = proc;
                tasks[task_id].start_time         = actual_start;
                tasks[task_id].finish_time        = actual_start + tasks[task_id].execution_time;

                processor_free_time[proc] = tasks[task_id].finish_time;
            }
        }

        for (int id : ready_ids) {
            if (tasks[id].finish_time != -1 && !done[id]) {
                done[id] = true;
                completed++;
            }
        }
    }

    return tasks;
}