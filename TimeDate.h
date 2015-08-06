#ifndef TIMEDATE_H
#define TIMEDATE_H


class TimeDate {
private:
    struct TimeCache {
        int hour;
        int min;
        int day;
        int month;
        int year;
        int week_day;
        unsigned long seconds = -1;
    };
    static const int TIMEZONE = 2;
    unsigned long seconds;
    TimeCache cache;
    void updateCache();
    static bool isLeapYear(int year);
    static int getDaysMonth(int month, int year);
public:
    TimeDate();
    TimeDate(int hour, int min, int day, int month, int year);
    bool refresh();
    int getHour();
    int getMin();
    int getDay();
    int getMonth();
    int getYear();
    int getDayOfWeek();
    bool is_AM();
    bool operator<(const TimeDate &b) const;
    unsigned long get_time_in_seconds();
    void set_time_seconds(unsigned long seconds);
    void set_time(int hour, int min, int day, int month, int year);
};

#endif // TIMEDATE_H
