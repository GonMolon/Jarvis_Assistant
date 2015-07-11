#include "Movimiento.h"
#include "Arduino.h"

Movimiento::Movimiento() {
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

bool Movimiento::is_light_fixed() const {
    return light_fixed;
}

int Movimiento::get_light_level() const {
    int light = analogRead(PIN_LIGHT);
    if(light > light_level_1) {
        return 1;
    } else if(light > light_level_2) {
        return 2;
    } else {
        return 3;
    }
}

bool Movimiento::refresh() {
    if(activado) {
        if(digitalRead(PIN_MOVIMIENTO)) {
            timer.reset();
            if(!movimiento) {
                movimiento = true;
                return true;
            }
        } else if(movimiento && timer.is_finished()){
            movimiento = false;
            return true;
        }
    }
    return false;
}

