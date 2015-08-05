#include "Jarvis.h"
#include "SOUNDS.h"

Jarvis::Jarvis() {
    vc.play(SND_inicio);
    int light1 = mov.get_light();
    inter.changeLight();
    int light2 = mov.get_light();
    Serial.println(light2);
    if(light1 > light2) {
        inter.changeLight();
    }
    check_time();
    vc.readTrigger();
}

void Jarvis::refresh() {
    Serial.println(vc.is_sleeping());
    if(!vc.is_sleeping()) {
        Serial.println("hellou");
        if(mov.refresh(timer2)) {
            timer1.reset();
            if(mov.is_moving()) {
                sec_light_on();
            } else {
                ir.light_off();
            }
        } else if(!mov.is_moving()) {
            if(timer1.is_finished()) {
                sec_desaparecer();
            }
        }
        if(!vc.is_listening()) {
            if(vc.getTrigger() >= 0) {
                vc.play(0);
                sec_inicio();
            }
            vc.readTrigger();
        }
    }
    check_ir();
}

void Jarvis::sec_inicio() {
    int id = vc.readCommand(1, 3);
    if(id == 0) { //Apagar luz
        inter.off();
    } else if(id == 1) { //Encender luz
        inter.on();
    } else if(id == 2) { //Presentate
        vc.play(SND_presentate);
        sec_inicio();
    } else if(id == 3) { //Chiste
        sec_chiste();
    } else if(id == 4) { //Resumen
        vc.play(0);
        sec_resumen_dia();
    } else if(id == 5) { //Sleep mode
        vc.play(SND_pase_buen_dia);
        vc.desactivar();
    } else if(id == 6) { //Cancelar
        vc.play(0);
    } else if(id == 7) { //Ventilador on
        vc.play(0);
        ir.level_3();
    } else if(id == 8) { //Ventilador off
        vc.play(0);
        ir.level_0();
    } else if(id == 9) { //Hora
        sec_hora();
    } else if(id == 10) { //Dia
        sec_dia();
    } else if(id == 11) { //Weather
        sec_weather();
    } else if(id == 12) { //Poner musica
        sec_musica(7);
    } else if(id == 13) { //Menu musica
        sec_menu_musica();
    } else if(id == 14) { //Temperatura
        sec_temperatura();
    } else if(id == 15) { //Marcho
        sec_dormir();
    }
}

void Jarvis::check_ir() {
    long IRCode = ir.read();
    if(IRCode == IRtransmitter::SPEAKERS_ON) {
        if(vc.is_sleeping()) {
            vc.despertar();
        } else {
            vc.desactivar();
        }
    } else if(IRCode == IRtransmitter::SPEAKERS_MUTE) {
        mov.set_light_fixed(!mov.is_light_fixed());
    } else if(IRCode == IRtransmitter::SPEAKERS_HIGHER) {
        ir.level_3();
    } else if(IRCode == IRtransmitter::SPEAKERS_LOWER) {
        ir.level_0();
    } else if(IRCode == IRtransmitter::SPEAKERS_UP) {
        ir.light_on();
    } else if(IRCode == IRtransmitter::SPEAKERS_DOWN) {
        ir.light_off();
    }
}

void Jarvis::sec_light_on() {
    if(!mov.is_light_fixed()) {
        if(mov.is_dark()) {
            ir.light_on();
        }
    }
}

void Jarvis::sec_chiste() {
    int chiste = millis()%3;
    vc.play(SND_chiste_1+chiste);
}

void Jarvis::sec_resumen_dia() {
    sec_hora();
    sec_dia();
    sec_temperatura();
    sec_humedad();
    sec_weather();
}

bool Jarvis::check_time() {
    if(!time.is_set()) {
        if(!time.refresh()) {
            vc.play(SND_error_internet);
            return false;
        }
    }
    return true;
}

void Jarvis::sec_hora() {
    if(check_time()) {
        say_time(time.getHour(), time.getMin());
    } else {
        delay(1000);
    }
}

void Jarvis::say_time(int hour, int min) {
    int index = hour%12 - 1;
    if(min > 30) {
        index = index + 1;
    }
    if(index < 0) {
       index = 11;
    }
    vc.play(SND_hora_1 + index);
    index = ((int)(min/double(5) + 0.5))%12; //arredondeando a 5 minutos
    vc.play(SND_min_0 + index);
    if(hour <= 12) {
        vc.play(SND_manana);
    } else {
        vc.play(SND_tarde);
    }
}

void Jarvis::sec_dia() {
    if(check_time()) {
        vc.play(SND_dia_1_lunes + time.getDayOfWeek() - 1);
        vc.play(SND_num_1 + time.getDay() - 1);
        vc.play(SND_mes_1_enero + time.getMonth() - 1);
    }
}


void Jarvis::sec_temperatura() {
    int temperatura = term.get_temperature();
    Serial.println(temperatura);
    if(temperatura != -1) {
        vc.play(SND_temperatura);
        vc.play(SND_num_0+temperatura);
        vc.play(SND_grados);
    }
}

void Jarvis::sec_humedad() {
    int humedad = term.get_humidity();
    Serial.println(humedad);
    if(humedad != -1) {
        vc.play(SND_num_0+humedad);
        vc.play(SND_humedad);
    }
}

void Jarvis::sec_dormir() {
    vc.play(SND_dormir_musica);
    bool music = vc.readCommand(2,3) == 0;
    vc.play(SND_despertador);
    bool despertador = vc.readCommand(2,3) == 0;
    int id;
    if(despertador) {
        vc.play(SND_cual);
        id = vc.readCommand(5, 3);
        if(id != -1) {
            vc.play(SND_alarma_on);
            if(despertador) {
                if(id == 1) {
                    say_time(8, 30);
                } else if(id == 2) {
                    say_time(9, 30);
                } else if(id == 3) {
                    say_time(10, 30);
                } else {
                    say_time(6, 30);
                }
            }
        } else {
            despertador = false;
        }
    }
    vc.play(SND_buenas_noches);
    ir.light_off();
    inter.off();
    if(music) {
        ir.speaker_on();
        ir.set_volume(5);
        ir.playlist(7);
        delay(200);
        ir.next();
        Timer apagar(20*60);
        while(!apagar.is_finished()) {
            check_ir();
            Serial.println(apagar.get_remaining());
        }
        ir.set_volume(0);
        ir.speaker_on();
    }
    vc.desactivar();
    if(despertador) {
        if(id == 1) {
            sec_despertador(8, 30);
        } else if(id == 2) {
            sec_despertador(9, 30);
        } else if(id == 3) {
            sec_despertador(10,30);
        } else {
            sec_despertador(6, 30);
        }
    } else {
        while(mov.is_moving()) {
            mov.refresh(timer2);
            Serial.println("Esperando a que se tumbe");
        }
        sec_despertar();
    }
}

void Jarvis::sec_despertar() {
    while(mov.get_light() > 500 || !mov.is_moving()) {
        mov.refresh(timer2);
    }
    vc.play(SND_buenos_dias);
    sec_resumen_dia();
    ir.level_0();
    vc.despertar();
}

void Jarvis::sec_despertador(int hora, int min) {
    unsigned long time_seconds = time.get_time_in_seconds();
    time.set_time(hora, min, time.getDay(), time.getMonth(), time.getYear());
    if(time.get_time_in_seconds() < time_seconds) {
        time.set_time_seconds(time.get_time_in_seconds()+(unsigned long)24*60*60);
    }
    sec_resumen_dia();
    unsigned int duration = time.get_time_in_seconds()-time_seconds;
    Timer alarm(duration);
    time.set_time_seconds(time_seconds);
    while(!alarm.is_finished()) {
        check_ir();
        Serial.println(alarm.get_remaining());
    }
    sec_musica(1);
    for(int i = 0; i < 4; ++i) {
        delay(1000);
        ir.volume_up();
    }
    sec_despertar();
}

void Jarvis::sec_aparecer() {
    sec_light_on();
    vc.play(SND_ido_dia);
    int id = vc.readCommand(3, 3);
    if(id == 0) { //Bien
        vc.play(SND_alegro);
    } else if(id == 1) { //Mal
        vc.play(SND_vaya);
        vc.play(SND_chiste_oir);
        if(vc.readCommand(2, 3) == 0) {
            sec_chiste();
            delay(500);
        }
    }
    if(term.get_temperature() >= 25) {
        vc.play(SND_ventilador);
        if(vc.readCommand(2, 3) == 0) { //SI
            vc.play(0);
            ir.level_3();
        }
    }
    vc.play(SND_escuchar_musica);
    if(vc.readCommand(2,3) == 0) {
        sec_musica(7);
    }
    vc.readTrigger();
}

void Jarvis::sec_desaparecer() {
    vc.play(SND_pase_buen_dia);
    ir.level_0();
    delay(500);
    ir.light_off();
    inter.off();
    delay(20*1000);
    while(!(mov.refresh(timer2) && mov.is_moving())) {}
    sec_aparecer();
}

void Jarvis::sec_weather() {

}

void Jarvis::sec_musica(int volumen) {
    vc.play(0);
    ir.speaker_on();
    /*ir.random();
    delay(500);
    ir.play();*/
    ir.set_volume(volumen);
    ir.play();
}

void Jarvis::sec_menu_musica() {
    vc.play(0);
    int id = vc.readCommand(4,3);
    if(id == 0) {
        ir.next();
    } else if(id == 1) {
        ir.previous();
        ir.previous();
    } else if(id == 2) {
        ir.speaker_on();
    } else if(id == 3) {
        ir.playlist(7);
    } else if(id == 4) {
        ir.volume_up();
    } else if(id == 4) {
        ir.volume_down();
    }
    vc.readTrigger();
}
