#include "task.h"
#include <cstdlib>
#include <ctime>

std::vector<Task> generateTasks(int num_tasks, int max_exec_time) {
    srand(time(0));

    std::vector<Task> tasks(num_tasks);

    for (int i = 0; i < num_tasks; i++) {
        tasks[i].id = i;

        tasks[i].execution_time = (rand() % 50) + 1;

        for (int j = 0; j < i; j++) {
            if (rand() % 5 == 0) {
                tasks[i].dependencies.push_back(j);
            }
        }
    }

    return tasks;
}