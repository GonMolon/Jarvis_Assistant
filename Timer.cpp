#include "Timer.h"
#include "Arduino.h"

Timer::Timer(int duration) {
    this->duration = duration;
}

void Timer::reset() {
    finishTime = millis() + duration*1000;
}

bool Timer::is_finished() const {
    return millis() >= finishTime;
}

int Timer::get_remaining() const {
    return (finishTime-millis())/1000;
}

