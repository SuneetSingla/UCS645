#pragma once
#include <vector>

struct Task {
    int id;                           // task number (0, 1, 2, etc)
    int execution_time;               // how many units of time it takes
    std::vector<int> dependencies;    // list of task IDs that must finish before this one
    int start_time  = -1;             // when it starts (-1 = not scheduled yet)
    int finish_time = -1;             // when it finishes
    int assigned_processor = -1;      // which processor runs it
};

std::vector<Task> generateTasks(int num_tasks, int max_exec_time = 10);