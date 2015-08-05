#include "Termometro.h"
#include "Arduino.h"

Termometro::Termometro() {
}

int Termometro::get_temperature() {
    int i = 3;
    while(i > 0) {
        if(dht.read(DHTPIN) == DHTLIB_OK) {
            return (int) (dht.temperature + 0.5);
        }
        --i;
    }
    return -1;
}

int Termometro::get_humidity() {
    int i = 3;
    while(i > 0) {
        if(dht.read(DHTPIN) == DHTLIB_OK) {
            return ((int) (dht.humidity/10 + 0.5))*10;
        }
        --i;
    }
    return -1;
}

