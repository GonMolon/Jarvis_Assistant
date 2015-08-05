#include "Movimiento.h"
#include "Arduino.h"

Movimiento::Movimiento() {
    pinMode(PIN_MOVIMIENTO, INPUT);
}

bool Movimiento::is_light_fixed() const {
    return light_fixed;
}

void Movimiento::set_light_fixed(bool light_fixed) {
    this->light_fixed = light_fixed;
}

bool Movimiento::is_moving() const {
    return movimiento;
}

bool Movimiento::is_dark() const {
    return LIGHT_LEVEL <= get_light();
}

int Movimiento::get_light() const {
    return analogRead(PIN_LIGHT);
}

bool Movimiento::refresh(Timer &timer) {
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
    return false;
}

