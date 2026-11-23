#pragma once

#include "Task.h"
#include "TaskStatus.h"
#include "ResultCode.h"
#include "PrintMode.h"
#include <unordered_map>

std::string toString(TaskStatus status);
class TaskManager { 
    private: 
         std::unordered_map<int,Task> tasks;
    protected: 
        static int nextID;
    public: 
        ResultCode createTask(const std::string& desc); 
        ResultCode updateTask(const int& id, const std::string& desc);
        ResultCode deleteTask(const int& id); 
        ResultCode markDone(const int& id); 
        ResultCode markInProgress(const int& id); 
        void findByStatus(TaskStatus status, std::vector<std::pair<int,Task>>& result);
        void findAllTasks(std::vector<std::pair<int,Task>>& result);
        void printOptionalDate(const Task& task); 
        void printTask(const int& id, const Task& task); 
        void printTasks(PrintMode mode); 
        TaskManager::TaskManager(); 
};
