#include "TimeDate.h"

TimeDate::TimeDate() {
    HttpRequest timeProvider;
    long seconds_from_1970 = timeProvider.getTime(TIMEZONE);
    if(seconds_from_1970 != -1) {
        setTime((unsigned long)seconds_from_1970);
    }
}

bool TimeDate::is_set() {
    return timeStatus() != timeNotSet;
}

unsigned long TimeDate::get_time_in_seconds() {
    return now();
}

int TimeDate::getHour() {
    return hour();
}

int TimeDate::getMin() {
    return minute();
}

int TimeDate::getDay() {
    return day();
}

int TimeDate::getMonth() {
    return month();
}

int TimeDate::getYear() {
    return year();
}

int TimeDate::getDayOfWeek() {
    return weekday()-1+7*(weekday()==1);
}

bool TimeDate::is_AM() {
    return isAM();
}

void TimeDate::set_time_seconds(unsigned long seconds) {
    setTime(seconds);
}

void TimeDate::set_time(int hour, int min, int day, int month, int year) {
    setTime(hour, min, 0, day, month, year);
}

bool TimeDate::refresh() {
    HttpRequest timeProvider;
    time_t new_time = timeProvider.getTime(TIMEZONE);
    if(new_time != -1) {
        setTime(new_time);
        return true;
    } else {
        return false;
    }
}
