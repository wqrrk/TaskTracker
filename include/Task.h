#pragma once

#include <optional>
#include "Date.h"

struct Task { 
    std::string description; 
    TaskStatus status;

    Date createdAt;
    std::optional<Date> updatedAt;
    
    Task::Task(const std::string& description);
};