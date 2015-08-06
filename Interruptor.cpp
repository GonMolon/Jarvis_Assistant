#include "Interruptor.h"
#include "Arduino.h"

Interruptor::Interruptor() {
    servo.attach(PIN_SERVO);
    servo.write(POS1);
    delay(WAIT_TIME);
    servo.detach();
}

void Interruptor::changeLight() {
    servo.attach(PIN_SERVO);
    int pos = servo.read();
    if (pos == POS1) {
        pos = POS2;
    } else {
        pos = POS1;
    }
    servo.write(pos);
    delay(WAIT_TIME);
    servo.detach();
}

void Interruptor::on() {
    if(!encendido) {
        changeLight();
    }
    encendido = true;
}

void Interruptor::off() {
    if(encendido) {
        changeLight();
    }
    encendido = false;
}
