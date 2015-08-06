#include "Timer.h"
#include "Arduino.h"

Timer::Timer(unsigned int duration) {
    this->duration = duration;
    reset();
}

void Timer::reset() {
    finishTime = millis() + ((unsigned long) duration)*1000;
}

bool Timer::is_finished() const {
    Serial.println((finishTime - millis())/1000);
    return millis() > finishTime;
}

long Timer::get_remaining() const {
    return (finishTime - millis())/1000;
}

