#include "Voicecontrol.h"
#include "SOUNDS.h"
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
    easyvr.setTimeout(TIMEOUT);
    easyvr.setLanguage(LANG);
    if(easyvr.setLevel(LEVEL)) {
        Serial.print("level cambiado: ");
        Serial.println(LEVEL);
    } else {
        Serial.println("Error al cambiar level");
    }
    sleeping = false;
}

void VoiceControl::readTrigger() {
    easyvr.recognizeCommand(0);
}

void VoiceControl::printName(int group, int id) {
    uint8_t training;
    char name[33];
    easyvr.dumpCommand(group, id, name, training);
    Serial.print("Command: ");
    Serial.println(name);
}

int VoiceControl::getTrigger() {
    int id = easyvr.getCommand();
    if (id >= 0) {
        printName(0, id);
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

int VoiceControl::readCommand(int group, int repet) {
    easyvr.stop();
    easyvr.recognizeCommand(group);
    while(is_listening()) {}
    int id = easyvr.getCommand();
    if(id >= 0) {
        printName(group, id);
        return id;
    } else {
        --repet;
        if(repet == 0) {
            play(SND_no_entendido);
            delay(1000);
            return -1;
        }
        return readCommand(group, repet);
    }
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
    readTrigger();
}

void VoiceControl::play(int track) {
    easyvr.stop();
    easyvr.playSound(track, VOLUME);
}

bool VoiceControl::is_sleeping() {
    return sleeping;
}

bool VoiceControl::is_listening() {
    return !easyvr.hasFinished();
}

void VoiceControl::set_volume(int volume) {
    this->VOLUME = volume;
}
