#include <Servo.h>

#ifndef INTERRUPTOR_H
#define INTERRUPTOR_H

class Interruptor {
    Servo servo;
    bool encendido = false;
    const int pos1 = 60; //8 //550
    const int pos2 = 160; //73 //1400
    const int PIN_SERVO = 8;
public:
    Interruptor();
    void changeLight();
    void on();
    void off();
};

#endif // INTERRUPT_H
