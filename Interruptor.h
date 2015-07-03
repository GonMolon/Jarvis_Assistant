#include <Servo.h>

#ifndef INTERRUPTOR_H
#define INTERRUPTOR_H

class Interruptor {
    Servo servo;
    const int pos1 = 60; //8 //550
    const int pos2 = 160; //73 //1400
    const int PIN_SERVO = 9;
public:
    Interruptor();
    void changeLight();
};

#endif // INTERRUPT_H
