#ifndef TIMER_H
#define TIMER_H

class Timer {
    unsigned long finishTime;
    unsigned int duration;
public:
    Timer(unsigned int duration);
    void reset();
    bool is_finished() const;
    long get_remaining() const;
};

#endif // TIMER_H
