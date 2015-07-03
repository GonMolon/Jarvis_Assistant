#ifndef JARVIS_H
#define JARVIS_H

#include "Voicecontrol.h"
#include "Interruptor.h"
#include "IRtransmitter.h"
#include "Movimiento.h"
#include "Termometro.h"

class Jarvis {
  private:
    VoiceControl vc;
    Interruptor inter;
    IRtransmitter ir;
    Movimiento mov;
    Termometro term;
    bool alarma = false;
    void logicAction(int id);
    void resumen_dia();
    void hora();
    void dia();
  public:
    Jarvis();
    void setup();
    void refresh();
};

#endif
