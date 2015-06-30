#include "Jarvis.h"
#include "Constants.h"

Jarvis::Jarvis() {

}

void Jarvis::setup() {
    vc.setup();
    ir.setup();
    vc.readCommand();
}

void Jarvis::refresh() { 
    /*if(mov.refresh()) {
      
        //inter.changeLight();
    }*/
    if(!vc.is_sleeping() && !vc.is_listening()) {
        int id = vc.getCommand();
        if(id >= 0) {
            logicAction(id);
        } else {
            //PERDONE, NO LE HE ENTENDIDO
        }
        if(!vc.is_sleeping()) {
            vc.readCommand();
        }
    }
    /*long IRCode = ir.read();
    if(vc.is_sleeping() && IRCode == IRtransmitter::ENCENDER) {
        vc.despertar();
    }*/
}

void Jarvis::logicAction(int id) {
    if (vc.get_group() == 0) { //Trigger
        vc.play(0);
        if(id == 0) {
            vc.set_group(1);
        }
    } else if (vc.get_group() == 1) {
        if(id == 0 || id == 1) { //Enceder/apagar luz
            inter.changeLight();
            vc.set_group(0);
        } else if(id == 2) { //Presentate
            vc.play(SND_presentate);
        } else if(id == 3) { //Chiste
            int chiste = random(0, 4);
            vc.play(SND_chiste_1+chiste);
            vc.set_group(0);
        } else if(id == 4) { //Resumen
            resumen_dia();
            vc.set_group(0);
        } else if(id == 5) { //Sleep mode
            vc.play(SND_pase_buen_dia);
            vc.desactivar();
            vc.set_group(0);
        } else if(id == 6) { //Cancelar
            vc.play(0);
            vc.set_group(0);
        } else if(id == 7) { //Poner m�sica
            vc.play(0);
            ir.start();
            vc.set_group(0);
        } else if(id == 8) { //Hora
            hora();
            vc.set_group(0);
        } else if(id == 9) { //Dia
            dia();
            vc.set_group(0);
        } else if(id == 10) { //Soy un crack?
            vc.play(SND_si);
            vc.set_group(0);
        } else if(id == 8 || id == 9) { //Sensor movimiento
            if(id == 8) {
                vc.play(SND_movimiento_on);
            } else {
                vc.play(SND_movimiento_off);
            }
            mov.set_activated(!mov.is_activated());
            vc.set_group(0);
        } else if(id == 12 || id == 13) { //Alarma on
            if(id == 12) {
                vc.play(SND_alarma_on);
            } else {
                vc.play(SND_alarma_off);
            }
            alarma = !alarma;
            vc.set_group(0);
        }
    }
}

void Jarvis::resumen_dia() {
    hora();
    dia();
}

void Jarvis::hora() {
    vc.play(SND_hora_10);
    vc.play(SND_min_5);
}

void Jarvis::dia() {
    vc.play(SND_dia_5_viernes);
    vc.play(SND_num_8);
    vc.play(SND_mes_5_mayo);
}
