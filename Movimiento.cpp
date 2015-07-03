#include "Movimiento.h"
#include "Arduino.h"

Movimiento::Movimiento() {
    pinMode(PIN_LED, OUTPUT);
    pinMode(PIN_MOVIMIENTO, INPUT);
}

bool Movimiento::is_activated() const {
    return activado;
}

void Movimiento::set_activated(bool activado) {
    this->activado = activado;
}

bool Movimiento::is_moving() const {
    return movimiento;
}

bool Movimiento::refresh() {
    if(activado) {
        if(digitalRead(PIN_MOVIMIENTO)) {
            timer.reset();
            if(!movimiento) {
                movimiento = true;
                digitalWrite(PIN_LED, HIGH);
                return true;
            }
        } else if(movimiento && timer.is_finished()){
            movimiento = false;
            digitalWrite(PIN_LED, LOW);
            return true;
        }
    }
    return false;
}

