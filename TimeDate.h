#ifndef TIMEDATE_H
#define TIMEDATE_H

class TimeDate {
    int hour;
    int min;
    int day;
    int month;
    int year;
    void setMilliseconds(unsigned long milli);
public:
    TimeDate();
    void refresh();
    int getHour();
    int getMin();
    int getDay();
    int getMonth();
    int getYear();
};

#endif // TIMEDATE_H
