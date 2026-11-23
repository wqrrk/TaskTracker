#include "Task.h"
#include <string>
#include <optional>
#include "TaskStatus.h"
#include "Date.h"

Task::Task(const std::string& description) { 
    //init fields
    this->description = description;
    this->status = TaskStatus::todo;
    
    //init dates 
    createdAt = Date();
    updatedAt = std::nullopt;
}