#include "Jarvis.h"
#include "SOUNDS.h"
#include "Timetable.h"

Jarvis::Jarvis() {
    vc.play(SND_inicio);
    int light1 = mov.get_light();
    inter.changeLight();
    int light2 = mov.get_light();
    if(light1 > light2) {
        inter.changeLight();
    }
    check_time();
    vc.readTrigger();
}

void Jarvis::refresh() {
    if(!vc.is_sleeping()) {
        if(mov.refresh(timer2)) {
            timer1.reset();
            if(mov.is_moving()) {
                sec_light_on();
            } else {
                if(!mov.is_light_fixed()) {
                    ir.light_off();
                }
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
    int id = vc.readCommand(1, VoiceControl::REPETITIONS);
    if(id == 0) { //Apaga la luz
        inter.off();
    } else if(id == 1) { //Enciende la luz
        inter.on();
    } else if(id == 2) { //Presentate
        vc.play(SND_presentate);
        //sec_inicio();
    } else if(id == 3) { //Cuentame un chiste
        sec_chiste();
    } else if(id == 4) { //Resumen del dia
        vc.play(0);
        sec_resumen_dia();
    } else if(id == 5) { //Desactivate
        vc.play(SND_pase_buen_dia);
        vc.desactivar();
    } else if(id == 6) { //Cancelar
        vc.play(0);
    } else if(id == 7) { //Enciende, el ventilador
        vc.play(0);
        ir.level_3();
    } else if(id == 8) { //Apaga el ventilador
        vc.play(0);
        ir.level_0();
    } else if(id == 9) { //Que hora es?
        vc.play(0);
        sec_hora();
    } else if(id == 10) { //Pon musica
        sec_musica();
    } else if(id == 11) { //Controlar ipod
        vc.play(0);
        sec_menu_musica();
    } else if(id == 12) { //Que temperatura hay?
        sec_temperatura();
    } else if(id == 13) { //Me voy
        vc.play(SND_pase_buen_dia);
        sec_desaparecer();
    } else if(id == 14) { //Desconectalo todo
        sec_apagar_todo();
    } else if(id == 15) { //Buenas noches
        sec_dormir();
    }
}

void Jarvis::check_ir() {
    long IRCode = ir.read();
    if(IRCode == IRtransmitter::SPEAKERS_VIDEO) {
        Serial.println(ir.isControllingSpeakers());
        ir.setControllingSpeakers(!ir.isControllingSpeakers());
        Serial.println(ir.isControllingSpeakers());
    } else {
        if(ir.isControllingSpeakers()) {
            if(IRCode == IRtransmitter::SPEAKERS_ON) {
                ir.speaker_on();
            } else if(IRCode == IRtransmitter::SPEAKERS_HIGHER) {
                ir.volume_up();
            } else if(IRCode == IRtransmitter::SPEAKERS_LOWER) {
                ir.volume_down();
            } else if(IRCode == IRtransmitter::SPEAKERS_UP) {
                ir.up();
            } else if(IRCode == IRtransmitter::SPEAKERS_DOWN) {
                ir.down();
            } else if(IRCode == IRtransmitter::SPEAKERS_MENU) {
                ir.menu();
            } else if(IRCode == IRtransmitter::SPEAKERS_SELECT) {
                 ir.select();
            } else if(IRCode == IRtransmitter::SPEAKERS_PREVIOUS) {
                ir.previous();
            } else if(IRCode == IRtransmitter::SPEAKERS_PLAY) {
                ir.play();
            } else if(IRCode == IRtransmitter::SPEAKERS_NEXT) {
                ir.next();
            }
        } else {
            if(IRCode == IRtransmitter::SPEAKERS_ON) {
                if(vc.is_sleeping()) {
                    vc.despertar();
                    timer1.reset();
                    vc.play(0);
                    vc.play(0);
                } else {
                    vc.play(SND_pase_buen_dia);
                    vc.desactivar();
                }
            } else if(IRCode == IRtransmitter::SPEAKERS_MUTE) {
                vc.play(0);
                mov.set_light_fixed(!mov.is_light_fixed());
                if(!mov.is_light_fixed()) {
                    if(mov.is_moving()) {
                        ir.light_on();
                    } else {
                        ir.light_off();
                    }
                } else {

                }
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
    sec_temperatura();
    sec_humedad();
    sec_horario();
}

bool Jarvis::check_time() {
    if(!time.refresh()) {
        vc.play(SND_error_internet);
        return false;
    } else {
        return true;
    }
}

void Jarvis::sec_hora() {
    if(check_time()) {
        vc.play(SND_son);
        say_time(time.getHour(), time.getMin());
        vc.play(SND_hoy_es);
        vc.play(SND_dia_1_lunes + time.getDayOfWeek()-1);
        vc.play(SND_num_1 + time.getDay() - 1);
        vc.play(SND_mes_1_enero + time.getMonth() - 1);
    } else {
        delay(1000);
    }
}

void Jarvis::say_time(int hour, int min) {
    int index = hour%12 - 1;
    if(min > 32) {
        index = index + 1;
    }
    if(index < 0) {
       index = 11;
    }
    vc.play(SND_hora_1 + index);
    index = ((int)(min/double(5) + 0.5))%12; //arredondeando a multiple de 5
    vc.play(SND_min_0 + index);
    if(hour <= 12) {
        vc.play(SND_manana);
    } else {
        vc.play(SND_tarde);
    }
}

void Jarvis::sec_temperatura() {
    int temperatura = term.get_temperature();
    if(temperatura != -1) {
        vc.play(SND_temperatura);
        vc.play(SND_num_0+temperatura);
        vc.play(SND_grados);
    }
}

void Jarvis::sec_humedad() {
    int humedad = term.get_humidity();
    if(humedad != -1) {
        vc.play(SND_num_0+humedad);
        vc.play(SND_humedad);
    }
}

void Jarvis::sec_dormir() {
    vc.play(SND_dormir_musica);
    bool music = vc.readCommand(2, VoiceControl::REPETITIONS) == 0;
    vc.play(SND_despertador);
    bool despertador = vc.readCommand(2, VoiceControl::REPETITIONS) == 0;
    int id;
    if(despertador) {
        vc.play(SND_cual);
        id = vc.readCommand(5, VoiceControl::REPETITIONS);
        if(id != -1) {
            vc.play(SND_alarma_activada);
            vc.play(SND_a);
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
            vc.play(SND_alarma_cancelada);
            despertador = false;
        }
    }
    vc.play(SND_buenas_noches);
    ir.light_off();
    inter.off();
    vc.desactivar();
    if(despertador) {
        if(id == 1) {
            sec_despertador(8, 30, music);
        } else if(id == 2) {
            sec_despertador(9, 30, music);
        } else if(id == 3) {
            sec_despertador(10,30, music);
        } else {
            sec_despertador(6, 30, music);
        }
    } else {
        if(music) {
            music_timer(20);
        }
        while(mov.is_moving()) {
            mov.refresh(timer2);
        }
        sec_despertar();
    }
}

void Jarvis::sec_despertar() {
    while(mov.get_light() > 500 || !mov.is_moving()) {
        mov.refresh(timer2);
        check_ir();
    }
    vc.play(SND_buenos_dias);
    sec_resumen_dia();
    ir.level_0();
    vc.despertar();
    timer1.reset();
}

void Jarvis::music_timer(int min) {
    ir.speaker_on();
    ir.set_volume(2);
    ir.playlist(7);
    delay(200);
    ir.next();
    Timer apagar(min*60);
    while(!apagar.is_finished()) {
        check_ir();
    }
    ir.set_volume(0);
    ir.speaker_on();
}

void Jarvis::sec_despertador(int hora, int min, bool music) {
    if(!check_time()) {
        vc.play(SND_alarma_cancelada);
        if(music) {
            music_timer(20);
        }
    } else {
        TimeDate alarmTime(hora, min, time.getDay(), time.getMonth(), time.getYear());
        if(alarmTime < time) {
            alarmTime.set_time_seconds(alarmTime.get_time_in_seconds()+(unsigned long)24*3600);
        }
        unsigned int duration = alarmTime.get_time_in_seconds()-time.get_time_in_seconds();
        Timer alarm(duration);
        if(music) {
            music_timer(20);
        }
        while(!alarm.is_finished()) {
            check_ir();
        }
        ir.set_volume(0);
        sec_musica();
        for(int i = 0; i < 3; ++i) {
            delay(7000);
            ir.volume_up();
        }
    }
    sec_despertar();
    ir.random();
}

void Jarvis::sec_aparecer() {
    sec_light_on();
    vc.play(SND_ido_dia);
    int id = vc.readCommand(3, VoiceControl::REPETITIONS);
    if(id == 0) { //Bien
        vc.play(SND_alegro);
    } else if(id == 1) { //Mal
        vc.play(SND_vaya);
        vc.play(SND_chiste_oir);
        if(vc.readCommand(2, VoiceControl::REPETITIONS) == 0) {
            sec_chiste();
            delay(500);
        }
    }
    if(term.get_temperature() >= 26) {
        vc.play(SND_ventilador);
        if(vc.readCommand(2, VoiceControl::REPETITIONS) == 0) { //SI
            vc.play(0);
            ir.level_3();
        }
    }
    vc.play(SND_escuchar_musica);
    if(vc.readCommand(2, VoiceControl::REPETITIONS) == 0) {
        sec_musica();
    }
    vc.readTrigger();
}

void Jarvis::sec_desaparecer() {
    sec_apagar_todo();
    while(mov.is_moving()) {
        mov.refresh(timer2);
    }
    while(!(mov.refresh(timer2) && mov.is_moving())) {}
    sec_aparecer();
}

void Jarvis::sec_weather() {

}

void Jarvis::sec_musica() {
    vc.play(0);
    ir.speaker_on();
    ir.play();
}

void Jarvis::sec_menu_musica() {
    int id = vc.readCommand(4, VoiceControl::REPETITIONS);
    if(id >= 0) {
        vc.play(0);
    }
    if(id == 0) { //Siguiente cancion
        ir.next();
    } else if(id == 1) { //Cancion anterior
        ir.previous();
        ir.previous();
    } else if(id == 2) { //Apaga los altavoces
        ir.speaker_on();
    } else if(id == 3) { //Sube el volumen
        ir.volume_up();
    } else if(id == 4) { //Baja el volumen
        ir.volume_down();
    } else if(id == 5) { //Modo aleatorio
        ir.random();
    }
}

void Jarvis::sec_horario() {
    Timetable::HorarioDia horario = Timetable::getHorario(time.getDayOfWeek());
    if(horario.ocho == -1 && horario.diez == -1 && horario.doce == -1) {
        vc.play(SND_no_clase);
    } else {
        vc.play(SND_clases);
        int clase;
        for(int i = 0; i < 3; ++i) {
            if(i == 0) {
                clase = horario.ocho;
            } else if (i == 1) {
                clase = horario.diez;
            } else {
                clase = horario.doce;
            }
            if(clase != -1) {
                say_clase(clase, 8+i*2);
            }
        }
    }
    if(time.getDayOfWeek() < 6) {
        vc.play(SND_faltan);
        vc.play(SND_num_0+(6-time.getDayOfWeek()));
        vc.play(SND_dias);
    }
}

void Jarvis::say_clase(int clase, int hora) {
    if(clase%2 != 0) {
        vc.play(SND_laboratorio);
    } else {
        vc.play(SND_teoria);
    }
    clase = ((double)clase)/2 + 0.5;
    vc.play(SND_clases_BD+clase-1);
    vc.play(SND_a);
    say_time(hora, 0);
    delay(500);
}

void Jarvis::sec_apagar_todo() {
    ir.level_0();
    delay(500);
    ir.light_off();
    inter.off();
}
