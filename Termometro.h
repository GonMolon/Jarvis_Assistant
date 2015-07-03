#ifndef TERMOMETRO_H
#define TERMOMETRO_H

class Termometro {
    const int PIN_TERM = 2;
public:
    Termometro();
    int get_temperature();
};

#endif // TERMOMETRO_H
