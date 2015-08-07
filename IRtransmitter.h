#ifndef IRTRANSMITTER_H
#define IRTRANSMITTER_H

#include "Arduino.h"
#include "IRremote.h"

class IRtransmitter {
private:
    static const int PIN_IR_SEND = 3;
    static const int PIN_IR_RECV = 7;
    static const int WAIT_TIME = 200;
    IRrecv irrecv = IRrecv(PIN_IR_RECV);
    IRsend irsend;
    decode_results results;
    bool speakersControl = false;
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
    void random();
    void play();
    void next();
    void previous();
    void playlist(int id);
    void set_volume(int v);
    void volume_up();
    void volume_down();
    void up();
    void down();
    void menu();
    void select();

    void light_on();
    void light_off();
    void level_0();
    void level_3();

    bool isControllingSpeakers() const;
    void setControllingSpeakers(bool controlling);
    long read();
};

#endif // IRTRANSMITTER_H
