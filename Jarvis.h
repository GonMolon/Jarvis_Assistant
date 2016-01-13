#ifndef JARVIS_H
#define JARVIS_H

#include "Voicecontrol.h"
#include "Interruptor.h"
#include "IRtransmitter.h"
#include "Movimiento.h"
#include "Termometro.h"
#include "TimeDate.h"
#include "Timer.h"

class Jarvis {
  private:
    VoiceControl vc;
    Interruptor inter;
    IRtransmitter ir;
    Movimiento mov;
    Termometro term;
    TimeDate time;
    Timer timer1 = Timer(60*60);
    Timer timer2 = Timer(Movimiento::INTERVAL);
    bool alarma = false;
    static const int MUSIC_TIMER = 25;
    void sec_inicio();
    void sec_resumen_dia();
    bool sec_hora();
    void say_time(int hour, int min);
    bool check_time();
    void sec_temperatura();
    void sec_humedad();
    void sec_dormir();
    void sec_despertar();
    void sec_despertador(int hora, int min, bool music);
    void sec_aparecer();
    void sec_desaparecer();
    void sec_apagar_todo();
    void sec_menu_musica();
    void sec_chiste();
    void sec_light_on();
    void sec_horario();
    void say_clase(int clase, int hora);
    void music_timer(int min);
    void check_ir();
    void simulador();
  public:
    Jarvis();
    void refresh();
};

#endif
