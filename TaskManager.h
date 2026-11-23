#pragma once

#include <unordered_map>

using namespace std;

enum class TaskStatus { 
    todo,
    in_progress,
    done 
};

//implement custom error codes for failures, done as a result code
enum class ResultCode { 
    success,
    incorrect_description,
    task_not_exists,
    task_already_marked_done,
    task_already_marked_in_progress,
};

enum class PrintMode { 
    all,
    done, 
    todo,
    in_progress
};

std::string toString(TaskStatus status);

struct Date { 
    int year; 
    int month; 
    int day; 
    int hour; 
    int minutes;

    Date();
}; 

struct Task { 
    string description; 
    string status;
    Date createdAt;
    bool updated;
    optional<Date> updatedAt;
    
    Task(string& description);
};

class TaskManager { 
    private: 
         unordered_map<int,Task> tasks;
    protected: 
        static int nextID;
    public: 
        ResultCode createTask(const string& desc); 
        ResultCode updateTask(const int& id, const string& desc);
        ResultCode deleteTask(const int& id); 
        ResultCode markDone(const int& id); 
        ResultCode markInProgress(const int& id); 
        void findByStatus(TaskStatus status, vector<pair<int,Task>>& result);
        void findAllTasks(vector<pair<int,Task>>& result);
        void printOptionalDate(const Task& task); 
        void printTask(const int& id, const Task& task); 
        void printTasks(PrintMode mode); 

        TaskManager::TaskManager(); 
};
