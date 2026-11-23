#include "Date.h"
#include <chrono>

Date::Date() { 
    //get current time
    auto now = std::chrono::system_clock::now();
    auto days = std::chrono::floor<std::chrono::days>(now);
    //convert 
    std::chrono::year_month_day ymd{days};
    std::chrono::hh_mm_ss hms{now-days}; 
    //set ymd
    this->year = static_cast<int>(ymd.year());
    this->month = static_cast<unsigned>(ymd.month()); 
    this->day = static_cast<unsigned>(ymd.day()); 
    //set hm
    this->hour = static_cast<int>(hms.hours().count());
    this->minutes = static_cast<int>(hms.minutes().count());
}

//overload the << operator so it can easily print our date 
std::ostream& operator<<(std::ostream& os, const Date& date) { 
os << date.day << "."
    << date.month << "."
    << date.year << " "
    << date.hour << ":"
    << date.minutes;
return os;
}