#ifndef IRTRANSMITTER_H
#define IRTRANSMITTER_H

#include "Arduino.h"
#include "IRremote.h"

class IRtransmitter {
private:
    static const int PIN_IR_SEND = 3;
    static const int PIN_IR_RECV = 7;
    IRrecv irrecv = IRrecv(PIN_IR_RECV);
    IRsend irsend;
    decode_results results;
    void sendIR(unsigned long ircode);
public:
    static const unsigned long ENCENDER = 0xE0E0C23D;
    static const unsigned long MUTE = 0xE0E022DD;
    static const unsigned long UP = 0xE0E002FD;
    static const unsigned long MENU = 0xE0E0827D;
    static const unsigned long SELECT = 0xE0E0807F;
    static const unsigned long DOWN = 0xE0E0A05F;
    static const unsigned long PREVIOUS = 0xE0E010EF;
    static const unsigned long PLAY = 0xE0E020DF;
    static const unsigned long NEXT = 0xE0E0E01F;
    static const unsigned long LOWER = 0xE0E0906F;
    static const unsigned long HIGHER = 0xE0E0609F;
    static const unsigned long VIDEO = 0xE0E0926D;
    IRtransmitter();
    void setup();
    void start();
    void play();
    void next();
    void previous();
    void playlist(int id);
    long read();
};

#endif // IRTRANSMITTER_H
