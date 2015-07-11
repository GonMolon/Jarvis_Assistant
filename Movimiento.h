#ifndef MOVIMIENTO_H
#define MOVIMIENTO_H

#include "Timer.h"

class Movimiento{
    const int PIN_MOVIMIENTO = 6;
    const int PIN_LIGHT = 5;
    const int interval = 8;
    const int light_level_1 = 400; //400 - infinito -> level 1
    const int light_level_2 = 200; //200 - 400 -> level 2
    const int light_level_3 = 0; //0 - 200 -> level 3
    bool activado = true;
    bool movimiento = false;
    bool light_fixed = false;
    Timer timer = Timer(interval);
public:
    Movimiento();
    bool is_activated() const;
    void set_activated(bool activated);
    bool is_moving() const;
    bool is_light_fixed() const;
    int get_light_level() const;
    bool refresh();
};

#endif // MOVIMIENTO_H
