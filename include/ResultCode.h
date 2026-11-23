#pragma once

//implement custom error codes for failures, done as a result code
enum class ResultCode { 
    success,
    incorrect_description,
    task_not_exists,
    task_already_marked_done,
    task_already_marked_in_progress,
};