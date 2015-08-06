#include "TimeDate.h"
#include "HttpRequest.h"

TimeDate::TimeDate() {
    cache.seconds = -1;
}

TimeDate::TimeDate(int hour, int min, int day, int month, int year) {
    cache.seconds = -1;
    set_time(hour, min, day, month, year);
}

void TimeDate::updateCache() {
    if(seconds != cache.seconds) {
        cache.seconds = seconds/60;
        cache.min = cache.seconds%60;
        cache.seconds = cache.seconds/60;
        cache.hour = cache.seconds%24;
        cache.seconds = cache.seconds/24;
        cache.week_day = (cache.seconds+4)%7;
        if(cache.week_day == 0) {
            cache.week_day = 7;
        }
        cache.year = 1970;
        cache.day = 0;
        while((unsigned)(cache.day += (isLeapYear(cache.year) ? 366 : 365)) <= cache.seconds) {
            ++cache.year;
        }
        cache.day -= isLeapYear(cache.year) ? 366 : 365;
        cache.seconds -= cache.day;
        cache.month = 1;
        while((signed)cache.seconds - getDaysMonth(cache.month, cache.year) > 0) {
            cache.seconds -= getDaysMonth(cache.month, cache.year);
            ++cache.month;
        }
        cache.day = cache.seconds+1;
        cache.seconds = seconds;
    }
}

bool TimeDate::operator<(const TimeDate &b) const {
    return seconds < b.seconds;
}

int TimeDate::getHour() {
    updateCache();
    return cache.hour;
}

int TimeDate::getMin() {
    updateCache();
    return cache.min;
}

int TimeDate::getDay() {
    updateCache();
    return cache.day;
}

int TimeDate::getMonth() {
    updateCache();
    return cache.month;
}

int TimeDate::getYear() {
    updateCache();
    return cache.year;
}

int TimeDate::getDayOfWeek() {
    updateCache();
    return cache.week_day;
}

bool TimeDate::is_AM() {
    updateCache();
    return cache.hour < 12;
}

unsigned long TimeDate::get_time_in_seconds() {
    return seconds;
}

void TimeDate::set_time_seconds(unsigned long seconds) {
    this->seconds = seconds;
}

void TimeDate::set_time(int hour, int min, int day, int month, int year) {
    int i = 1;
    while(i < month) {
        day += getDaysMonth(i, year);
        ++i;
    }
    --day;
    year = year-1900;
    seconds = min*60 + hour*3600 + day*86400 +
              (year-70)*31536000 + ((year-69)/4)*86400 -
              ((year-1)/100)*86400 + ((year+299)/400)*86400;
}

bool TimeDate::refresh() {
    HttpRequest timeProvider;
    seconds = timeProvider.getTime(TIMEZONE);
    return seconds != -1;
}

int TimeDate::getDaysMonth(int month, int year) {
    if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
        return 31;
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        return 30;
    } else {
        if(isLeapYear(year)) {
            return 29;
        } else {
            return 28;
        }
    }
}

bool TimeDate::isLeapYear(int year) {
    return year-1970 > 0 && year%4 == 0 && (year%100 != 0 || year%400 == 0);
}
