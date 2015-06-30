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
        if(movimiento != digitalRead(PIN_MOVIMIENTO)) {
            movimiento = !movimiento;
            digitalWrite(PIN_LED, movimiento);
            return true;
        }
    }
    return false;
}

