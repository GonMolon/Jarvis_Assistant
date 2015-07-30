#include "Jarvis.h"
#include "Constants.h"
#include "Database.h"
#include "HttpRequest.h"

Jarvis::Jarvis() {
    vc.play(SND_inicio);
    ir.light_off();
    delay(200);
    int light1 = mov.get_light();
    inter.changeLight();
    int light2 = mov.get_light();
    if(light1 < light2) {
        inter.changeLight();
    }
    vc.readCommand();
}

void Jarvis::refresh() { 
    if(!vc.is_sleeping()) {
        if(mov.refresh()) {
            if(mov.is_moving()) {
                if(!mov.is_light_fixed()) {
                    ir.light_on();
                    inter.on();
                }
                delay(200);
                ir.level_3();
            } else {
                if(!mov.is_light_fixed()) {
                    ir.light_off();
                    inter.off();
                }
                delay(200);
                ir.level_1();
            }
        }
        if(!vc.is_listening()) {
            int id = vc.getCommand();
            if(id >= 0) {
                logicAction(id);
            } else {
                vc.check_understood();
            }
            vc.readCommand();
        }
    }
    long IRCode = ir.read();
    if(vc.is_sleeping() && IRCode == IRtransmitter::SPEAKERS_ON) {
        vc.despertar();
    }
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
            mov.set_activated(!mov.is_activated());
            vc.set_group(0);
        } else if(id == 2) { //Presentate
            vc.play(SND_presentate);
        } else if(id == 3) { //Chiste
            int chiste = millis()%3;
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
        } else if(id == 7) { //Poner musica
            vc.play(0);
            ir.speaker_on();
            delay(200);
            ir.play();
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
    time.refresh();
    Serial.print(time.getHour());
    Serial.print(":");
    Serial.println(time.getMin());
    int index = time.getHour()%12 - 1;
    if(index < 0) {
       index = 11; 
    }
    vc.play(SND_hora_1+index);
    index = ((int)(time.getMin()/double(5) + 0.5))%12; //arredondeando a 5 minutos
    vc.play(SND_min_0+index);
    if(time.getHour() >= 12) {
        vc.play(SND_tarde);
    } else {
        vc.play(SND_manana);
    }
}

void Jarvis::dia() {
    vc.play(SND_dia_5_viernes);
    vc.play(SND_num_8);
    vc.play(SND_mes_5_mayo);
}
