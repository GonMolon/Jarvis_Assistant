#ifndef TIMER_H
#define TIMER_H

class Timer {
    unsigned long finishTime;
    int duration;
public:
    Timer(int duration);
    void reset();
    bool is_finished() const;
    int get_remaining() const;
};

#endif // TIMER_H
