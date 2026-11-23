#include <TaskManager.h>
#include <string>
#include <iostream>
#include <vector>
#include "Date.h"

int TaskManager::nextID = 0;

std::string toString(TaskStatus status) { 
    switch (status) { 
        case TaskStatus::todo: return "todo";
        case TaskStatus::done: return "done"; 
        case TaskStatus::in_progress: return "in-progress";
        default: return "invalid status";
    }
}

ResultCode TaskManager::createTask(const std::string& desc) { 
    if (desc.length() < 1) {
        //maybe later create an enum for custom errors
        return ResultCode::incorrect_description;
    }
    Task newTask = Task(desc); 
    tasks[++nextID] = newTask;
    return ResultCode::success;
}

ResultCode TaskManager::updateTask(const int& id, const std::string& desc) { 
    //check if exists task to update
    if (!tasks.contains(id)) { 
        return ResultCode::task_not_exists;
    }
    if (desc.length() < 1) { 
        return ResultCode::incorrect_description;
    }
    tasks[id].description = desc;
    return ResultCode::success;
}

ResultCode TaskManager::deleteTask(const int& id) {
    if(!tasks.contains(id)) { 
        return ResultCode::task_not_exists;
    }
    tasks.erase(id);
    return ResultCode::success;
}

ResultCode TaskManager::markDone(const int& id) { 
    if (!tasks.contains(id)) { 
        return ResultCode::task_not_exists;
    }
    Task* task = &tasks[id]; //could just to Task& task = tasks[id] tho
    if (task->status == TaskStatus::done) { 
        //some kind of error code like task is alr done idk later
        return ResultCode::task_already_marked_done;
    }
    task->status = TaskStatus::done; 
    return ResultCode::success;
}

ResultCode TaskManager::markInProgress(const int& id) { 
    if (!tasks.contains(id)) { 
        return ResultCode::task_not_exists;
    }
    Task& task = tasks[id];
    if (task.status == TaskStatus::in_progress) { 
        return ResultCode::task_already_marked_in_progress;
    }
    task.status = TaskStatus::in_progress;
    return ResultCode::success;
}

void TaskManager::findByStatus(TaskStatus status, std::vector<std::pair<int,Task>>& result) { 
    for (const auto& [id, task] : tasks) { 
        if (task.status == status) { 
            result.push_back(std::pair(id,task)); 
        }
    }
}

void TaskManager::findAllTasks(std::vector<std::pair<int,Task>>& result) { 
    for (const auto& [id, task] : tasks) { 
        result.push_back(std::pair(id,task));
    }
}

void TaskManager::printOptionalDate(const Task& task) { 
    if (task.updatedAt != std::nullopt) { 
        std::cout << task.updatedAt.value() << std::endl;
    }
}

void TaskManager::printTask(const int& id, const Task& task) { 
    std::cout << "=========" << std::endl;
    std::cout << "Task ID: " << id << std::endl; 
    std::cout << "DESC: " << task.description << std::endl;
    std::cout << "STATUS" << toString(task.status) << std::endl;
    std::cout << "" << task.createdAt << std::endl;
    printOptionalDate(task);
    std::cout << "========="; 
}

void TaskManager::printTasks(PrintMode mode) { 
    std::vector<std::pair<int,Task>> tasksToPrint; 
    switch (mode) {
        case PrintMode::all:  //list done tasks
            findAllTasks(tasksToPrint);
            break;
        case PrintMode::done: 
            findByStatus(TaskStatus::done, tasksToPrint);
            break;
        case PrintMode::in_progress: 
            findByStatus(TaskStatus::done, tasksToPrint);
            break;
        case PrintMode::todo: 
            findByStatus(TaskStatus::todo, tasksToPrint); 
            break;
    }
    for (const auto& [id, task] : tasksToPrint) { 
        printTask(id,task); 
    }
}
