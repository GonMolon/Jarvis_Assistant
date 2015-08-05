#ifndef TERMOMETRO_H
#define TERMOMETRO_H

#include <dht11.h>

#define DHTPIN 5

class Termometro {
private:
    dht11 dht;
public:
    Termometro();
    int get_temperature();
    int get_humidity();
};

#endif // TERMOMETRO_H
