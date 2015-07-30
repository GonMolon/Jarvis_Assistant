#include "Interruptor.h"
#include "Arduino.h"

Interruptor::Interruptor() {
    
}

void Interruptor::changeLight() {
    servo.attach(PIN_SERVO);
    int pos = servo.read();
    if (pos <= pos1 + 40) {
        pos = pos2;
    } else {
        pos = pos1;
    }
    for(int i = 0; i < 30; ++i) {
        servo.write(pos);
        delay(15);
    }
    servo.detach();
}

void Interruptor::on() {
    if(!enciendido) {
        changeLight();
    }
    encendido = true;
}

void Interrupor::off() {
    if(enciendido) {
        changeLight();
    }
    encendido = false;
}
