#ifndef VOICECONTROL_H
#define VOICECONTROL_H

#include <EasyVR.h>
#include <SoftwareSerial.h>

class VoiceControl {
private:
    SoftwareSerial  port = SoftwareSerial (2,3);
    EasyVR easyvr = EasyVR(port);
    const int lang = EasyVR::SPANISH;
    const int level = 1;
    const int vol = 31;
    const int timeout = 5;
    bool sleeping = false;
    int group = 0;
    
public:
    VoiceControl();
    void setup();
    bool is_sleeping();
    bool is_listening();
    int get_group();
    void set_group(int group);
    void readCommand();
    int getCommand();
    void play(int track);
    void desactivar();
    void despertar();
};

#endif // VOICECONTROL_H
