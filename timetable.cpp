#include "Timetable.h"

Timetable::HorarioDia Timetable::getHorario(int dia) {
    HorarioDia horario;
    horario.ocho = -1;
    horario.diez = -1;
    horario.doce = -1;
    if(dia == 1) {
        horario.ocho = SO_T;
        horario.diez = CI_L;
    } else if(dia == 2) {
        horario.ocho = PE_L;
        horario.diez = EDA_L;
        horario.doce = BD_L;
    } else if(dia == 4) {
        horario.ocho = CI_T;
        horario.diez = EDA_T;
    } else if(dia == 5) {
        horario.ocho = PE_T;
        horario.diez = SO_L;
        horario.doce = BD_T;
    }
}
