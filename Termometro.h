#ifndef TERMOMETRO_H
#define TERMOMETRO_H

#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT11 

class Termometro {
private:
    DHT dht = DHT(DHTPIN, DHTTYPE);
    float t = -1;
    float h = -1;
    float get_temperature();
    float get_humidity();
public:
    Termometro();
    void refresh();
};

#endif // TERMOMETRO_H
