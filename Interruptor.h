#include "ServoTimer2.h"

#ifndef INTERRUPTOR_H
#define INTERRUPTOR_H

class Interruptor {
    ServoTimer2  servo;
    static const int pos1 = 8;
    static const int pos2 = 73;
    static const int PIN_SERVO = 9;
public:
    Interruptor();
    void changeLight();
};

#endif // INTERRUPT_H
