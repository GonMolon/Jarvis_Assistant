#ifndef MOVIMIENTO_H
#define MOVIMIENTO_H

class Movimiento{
    const int PIN_MOVIMIENTO = 6;
    const int PIN_LED = 11;
    bool activado = true;
    bool movimiento = true;
public:
    Movimiento();
    bool is_activated() const;
    void set_activated(bool activated);
    bool is_moving() const;
    bool refresh();
};

#endif // MOVIMIENTO_H
