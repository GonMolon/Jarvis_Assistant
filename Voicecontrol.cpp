#include "Voicecontrol.h"
#include "Arduino.h"

VoiceControl::VoiceControl() {
    port.begin(9600);
    while (!easyvr.detect()) {
        Serial.println(F("EasyVR not detected!"));
        delay(1000);
    }
    Serial.print(F("EasyVR detected, version: "));
    Serial.println(easyvr.getID());
    easyvr.setPinOutput(EasyVR::IO1, HIGH);
    easyvr.setTimeout(timeout);
    easyvr.setLanguage(lang);
    easyvr.setLevel(level);
}

void VoiceControl::readCommand() {
    easyvr.recognizeCommand(group);
}

int VoiceControl::getCommand() {
    int id = easyvr.getCommand();
    if (id >= 0) {
        Serial.print(F("Command: "));
        Serial.println(id);
    } else {
        if (easyvr.isTimeout()) {
            Serial.println(F("Timed out, try again..."));
        }
        int16_t err = easyvr.getError();
        if (err >= 0) {
            Serial.print(F("Error 0x"));
            Serial.println(err, HEX);
        }
    }
    return id;
}

void VoiceControl::desactivar() {
    easyvr.stop();
    easyvr.setPinOutput(EasyVR::IO1, LOW);
    Serial.println(F("Sleep mode"));
    sleeping = easyvr.sleep(EasyVR::WAKE_ON_LOUDSOUND);
}

void VoiceControl::despertar() {
    sleeping = false;
    while(!easyvr.setPinOutput(EasyVR::IO1, HIGH)) {}
    readCommand();
}

void VoiceControl::play(int track) {
    easyvr.stop();
    easyvr.playSound(track, vol);
}

bool VoiceControl::is_sleeping() {
    return sleeping;
}

bool VoiceControl::is_listening() {
    return !easyvr.hasFinished();
}

int VoiceControl::get_group() {
    return group;
}

void VoiceControl::set_group(int group) {
    this->group = group;
}

