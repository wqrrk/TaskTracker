#pragma once

struct Date { 
    int year; 
    int month; 
    int day; 
    int hour; 
    int minutes;

    Date();
}; 

std::ostream& operator<<(std::ostream& os, const Date& date);