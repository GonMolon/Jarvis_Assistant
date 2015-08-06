#ifndef TIMETABLE
#define TIMETABLE

#include <arduino.h>

class Timetable {
public:
    struct HorarioDia {
        int ocho;
        int diez;
        int doce;
    };

    static const int BD_L = 1;
    static const int BD_T = 2;
    static const int CI_L = 3;
    static const int CI_T = 4;
    static const int EDA_L = 5;
    static const int EDA_T = 6;
    static const int PE_L = 7;
    static const int PE_T = 8;
    static const int SO_L = 9;
    static const int SO_T = 10;

    static HorarioDia getHorario(int dia);
};

#endif // TIMETABLE

