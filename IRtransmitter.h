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
    void sendNEC(unsigned long ircode);
    void sendRAW(unsigned int (&ircode)[99]);
public:
    static const unsigned long SPEAKERS_ON = 0xE0E0C23D;
    static const unsigned long SPEAKERS_MUTE = 0xE0E022DD;
    static const unsigned long SPEAKERS_UP = 0xE0E002FD;
    static const unsigned long SPEAKERS_MENU = 0xE0E0827D;
    static const unsigned long SPEAKERS_SELECT = 0xE0E0807F;
    static const unsigned long SPEAKERS_DOWN = 0xE0E0A05F;
    static const unsigned long SPEAKERS_PREVIOUS = 0xE0E010EF;
    static const unsigned long SPEAKERS_PLAY = 0xE0E020DF;
    static const unsigned long SPEAKERS_NEXT = 0xE0E0E01F;
    static const unsigned long SPEAKERS_LOWER = 0xE0E0906F;
    static const unsigned long SPEAKERS_HIGHER = 0xE0E0609F;
    static const unsigned long SPEAKERS_VIDEO = 0xE0E0926D;

    IRtransmitter();
    void speaker_on();
    void play();
    void next();
    void previous();
    void playlist(int id);

    void light_on();
    void light_off();
    void level_0();
    void level_1();
    void level_2();
    void level_3();
    
    long read();
};

#endif // IRTRANSMITTER_H
