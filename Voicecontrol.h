#ifndef VOICECONTROL_H
#define VOICECONTROL_H

#include <EasyVR.h>
#include <SoftwareSerial.h>

class VoiceControl {
private:
    SoftwareSerial  port = SoftwareSerial (2,9);
    EasyVR easyvr = EasyVR(port);
    static const int LANG = EasyVR::SPANISH;
    static const int LEVEL = 3;
    static const int VOL = 31;
    static const int TIMEOUT = 5;
    bool sleeping = false;
public:
    VoiceControl();
    void setup();
    bool is_sleeping();
    bool is_listening();
    int readCommand(int group, int repet);
    void readTrigger();
    int getTrigger();
    void play(int track);
    void desactivar();
    void despertar();
};

#endif // VOICECONTROL_H
