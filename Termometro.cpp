#include "Termometro.h"
#include "Arduino.h"

Termometro::Termometro() {
     dht.begin();
}

void Termometro::refresh() {
    float t = dht.readTemperature();
    float h = dht.readHumidity();
    if (isnan(t)) {
        this->t = t;
    }
    if (isnan(h)) {
        this->h = h;
    }
}

float Termometro::get_temperature() {
    return t;
}

float Termometro::get_humidity() {
    return h;
}

