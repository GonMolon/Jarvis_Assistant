#include "Termometro.h"
#include "Arduino.h"

Termometro::Termometro() {
  
}

int Termometro::get_temperature() {
    return analogRead(PIN_TERM);
}

