#ifndef MOVIMIENTO_H
#define MOVIMIENTO_H

#include "Timer.h"

class Movimiento{
    const int PIN_MOVIMIENTO = 6;
    const int PIN_LIGHT = 2;
    const int LIGHT_LEVEL = 800;
    bool movimiento = false;
    bool light_fixed = false;
public:
    static const unsigned int INTERVAL = 15;
    Movimiento();
    bool is_light_fixed() const;
    void set_light_fixed(bool light_fixed);
    bool is_moving() const;
    bool is_dark() const;
    int get_light() const;
    bool refresh(Timer &timer);
};

#endif // MOVIMIENTO_H
