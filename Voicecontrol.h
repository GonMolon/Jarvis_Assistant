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
    static const int VOLUME = 31;
    static const int TIMEOUT = 4;
    bool sleeping = false;
    void printName(int group, int id);
public:
    static const int REPETITIONS = 4;
    VoiceControl();
    void setup();
    bool is_sleeping();
    bool is_listening();
    int readCommand(int group, int repet);
    void readTrigger();
    int getTrigger();
    void play(int track);
    void set_volume(int vol);
    void desactivar();
    void despertar();
};

#endif // VOICECONTROL_H
