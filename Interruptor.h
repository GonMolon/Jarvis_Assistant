#include <Servo.h>

#ifndef INTERRUPTOR_H
#define INTERRUPTOR_H

class Interruptor {
    Servo servo;
    bool encendido = false;
    static const int POS1 = 70; //8 //550
    static const int POS2 = 170; //73 //1400
    static const int PIN_SERVO = 8;
    static const int WAIT_TIME = 500;
public:
    Interruptor();
    void changeLight();
    void on();
    void off();
};

#endif // INTERRUPT_H
