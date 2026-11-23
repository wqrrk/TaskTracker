#include <TaskManager.h>

#include <string>
#include <iostream>
#include <chrono>
#include <vector>


string toString(TaskStatus status) { 
    switch (status) { 
        case TaskStatus::todo: return "todo";
        case TaskStatus::done: return "done"; 
        case TaskStatus::in_progress: return "in-progress";
        default: return "invalid status";
    }
}

struct Date { 
    int year; 
    int month; 
    int day; 
    int hour; 
    int minutes;

    Date() { 
        //get current time
        auto now = chrono::system_clock::now();
        auto days = chrono::floor<chrono::days>(now);
        //convert 
        chrono::year_month_day ymd{days};
        chrono::hh_mm_ss hms{now-days}; 
        //set ymd
        this->year = static_cast<int>(ymd.year());
        this->month = static_cast<unsigned>(ymd.month()); 
        this->day = static_cast<unsigned>(ymd.day()); 
        //set hm
        this->hour = static_cast<int>(hms.hours().count());
        this->minutes = static_cast<int>(hms.minutes().count());
    }
};

//overload the << operator so it can easily print our date 
ostream& operator<<(ostream& os, const Date& date) { 
    os << date.day << "."
       << date.month << "."
       << date.year << " "
       << date.hour << ":"
       << date.minutes;
    return os;
}

struct Task { 
    string description; 
    TaskStatus status;

    Date createdAt;
    optional<Date> updatedAt;
    
    Task::Task(const string& description) { 
        //init fields
        this->description = description;
        this->status = TaskStatus::todo;
        
        //init dates 
        createdAt = Date();
        updatedAt = nullopt;
    }
};

class TaskManager { 
protected:
    static int nextID;
public: 
    unordered_map<int,Task> tasks;
    
    //add (create) a task
    ResultCode createTask(const string& desc) { 
        if (desc.length() < 1) {
            //maybe later create an enum for custom errors
            return ResultCode::incorrect_description;
        }
        Task newTask = Task(desc); 
        tasks[++nextID] = newTask;
        return ResultCode::success;
    }

    ResultCode updateTask(const int& id, const string& desc) { 
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

    ResultCode deleteTask(const int& id) {
        if(!tasks.contains(id)) { 
            return ResultCode::task_not_exists;
        }
        tasks.erase(id);
        return ResultCode::success;
    }

    ResultCode markDone(const int& id) { 
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

    ResultCode markInProgress(const int& id) { 
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

    void findByStatus(TaskStatus status, vector<pair<int,Task>>& result) const { 
        for (const auto& [id, task] : tasks) { 
            if (task.status == status) { 
                result.push_back(pair(id,task));
            }
        }
    }
    
    void findAllTasks(vector<pair<int,Task>>& result) { 
        for (const auto& [id, task] : tasks) { 
            result.push_back(pair(id,task));
        }
    }

    
    void printOptionalDate(const Task& task) { 
        if (task.updatedAt != nullopt) { 
            cout << task.updatedAt.value() << endl;
        }
    }

    void printTask(const int& id, const Task& task) { 
        cout << "=========" << endl;
        cout << "Task ID: " << id << endl; 
        cout << "DESC: " << task.description << endl;
        cout << "STATUS" << toString(task.status) << endl;
        cout << "" << task.createdAt << endl;
        printOptionalDate(task);
        cout << "========="; 
    }

    void printTasks(PrintMode mode) { 
        vector<pair<int,Task>> tasksToPrint; 
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

    //constructor
    TaskManager::TaskManager() { 
        int nextID = 0;
    }
};