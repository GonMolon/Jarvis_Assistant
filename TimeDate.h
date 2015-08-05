#ifndef TIMEDATE_H
#define TIMEDATE_H

#include <Time.h>
#include "HttpRequest.h"

class TimeDate {
    static const int TIMEZONE = 2;
    unsigned long milliseconds = -1;
    bool set = false;
public:
    TimeDate();
    bool is_set();
    bool refresh();
    int getHour();
    int getMin();
    int getDay();
    int getMonth();
    int getYear();
    int getDayOfWeek();
    unsigned long get_time_in_seconds();
    void set_time_seconds(unsigned long seconds);
    void set_time(int hour, int min, int day, int month, int year);
    bool is_AM();
};

#endif // TIMEDATE_H
