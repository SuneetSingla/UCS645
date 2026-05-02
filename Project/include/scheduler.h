#pragma once
#include "task.h"
#include <vector>
#include <string>

std::vector<Task> schedule(
    std::vector<Task> tasks,
    int num_processors,
    const std::string& algorithm
);