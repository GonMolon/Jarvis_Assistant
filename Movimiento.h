#ifndef MOVIMIENTO_H
#define MOVIMIENTO_H

#include "Timer.h"

class Movimiento{
    const int PIN_MOVIMIENTO = 6;
    const int PIN_LED = 5;
    const int INTERVAL = 8;
    bool activado = true;
    bool movimiento = false;
    Timer timer = Timer(INTERVAL);
public:
    Movimiento();
    bool is_activated() const;
    void set_activated(bool activated);
    bool is_moving() const;
    bool refresh();
};

#endif // MOVIMIENTO_H
