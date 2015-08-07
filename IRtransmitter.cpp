#include "IRtransmitter.h"

static unsigned int VENT_LIGHT_ON[99] = {450, 700, 550, 650, 550, 1550, 450, 1600, 500, 1600, 500, 1550, 500, 1600, 500, 700, 500, 1600, 500, 1550, 500, 1600, 450, 750, 450, 4550, 500, 700, 550, 650, 500, 1550, 550, 1550, 500, 1600, 450, 1600, 550, 1550, 500, 700, 500, 1550, 500, 1600, 500, 1600, 450, 700, 500, 4550, 550, 650, 500, 700, 450, 1600, 500, 1600, 500, 1550, 550, 1550, 500, 1600, 450, 750, 500, 1550, 500, 1600, 500, 1550, 550, 650, 500, 4650, 550, 650, 500, 700, 450, 1600, 500, 1600, 550, 1550, 500, 1550, 550, 1550, 450, 750, 450, 1600, 500, 1600, 450};
static unsigned int VENT_LIGHT_OFF[99] = {500, 700, 500, 650, 550, 1550, 500, 1600, 500, 1550, 500, 1600, 500, 1550, 550, 700, 450, 700, 500, 700, 500, 700, 450, 750, 450, 4550, 500, 700, 500, 700, 450, 1600, 500, 1600, 500, 1600, 450, 1600, 500, 1600, 450, 750, 500, 700, 450, 700, 500, 700, 500, 700, 450, 4600, 500, 700, 500, 700, 450, 1600, 450, 1600, 500, 1600, 500, 1600, 450, 1600, 500, 700, 500, 700, 500, 700, 500, 700, 450, 700, 500, 4700, 450, 700, 500, 700, 500, 1600, 450, 1600, 550, 1550, 500, 1550, 500, 1600, 500, 700, 500, 700, 450, 700, 500};
static unsigned int VENT_LEVEL_0[99] = {450, 750, 450, 750, 450, 1600, 450, 1600, 500, 1600, 500, 1600, 500, 1550, 550, 650, 500, 1600, 450, 1600, 550, 650, 550, 650, 500, 4550, 500, 700, 450, 700, 500, 1600, 500, 1600, 500, 1550, 550, 1550, 500, 1550, 500, 700, 500, 1600, 500, 1550, 500, 700, 550, 650, 500, 4550, 500, 700, 450, 700, 550, 1550, 450, 1650, 450, 1600, 500, 1600, 500, 1550, 550, 650, 500, 1550, 500, 1600, 550, 650, 500, 700, 500, 4700, 450, 700, 500, 700, 500, 1550, 550, 1550, 500, 1600, 500, 1550, 500, 1600, 500, 700, 500, 1550, 500, 1600, 500};
static unsigned int VENT_LEVEL_3[99] = {500, 700, 450, 750, 450, 1600, 500, 1600, 450, 1600, 500, 1600, 500, 1600, 450, 750, 450, 1600, 500, 700, 450, 750, 450, 750, 450, 4550, 500, 700, 500, 700, 450, 1600, 500, 1600, 500, 1600, 450, 1600, 500, 1600, 450, 750, 450, 1600, 500, 700, 500, 700, 500, 700, 450, 4600, 450, 700, 500, 700, 500, 1600, 450, 1600, 500, 1600, 450, 1600, 500, 1600, 500, 700, 450, 1650, 450, 700, 500, 750, 450, 700, 500, 4700, 450, 700, 500, 700, 500, 1600, 450, 1600, 500, 1600, 450, 1600, 500, 1600, 500, 700, 450, 1650, 450, 700, 500};

IRtransmitter::IRtransmitter() {
    irrecv.enableIRIn();
}

void IRtransmitter::speaker_on() {
    sendNEC(SPEAKERS_ON);
    delay(200);
}

void IRtransmitter::random() {
    for(int i = 0; i < 6; i++) {
        sendNEC(SPEAKERS_MENU);
        delay(WAIT_TIME);
    }
    for(int i = 0; i < 5; i++) {
        sendNEC(SPEAKERS_UP);
        delay(WAIT_TIME);
    }
    for(int i = 0; i < 4; i++) {
        sendNEC(SPEAKERS_DOWN);
        delay(WAIT_TIME);
    }
    sendNEC(SPEAKERS_SELECT);
}

void IRtransmitter::play() {
    sendNEC(SPEAKERS_PLAY);
}

void IRtransmitter::next() {
    sendNEC(SPEAKERS_NEXT);
}


void IRtransmitter::previous() {
    sendNEC(SPEAKERS_PREVIOUS);
}

void IRtransmitter::set_volume(int v) {
    for(int i = 0; i < 20; ++i) {
        sendNEC(SPEAKERS_LOWER);
        delay(WAIT_TIME);
    }
    for(int i = 0; i < v; ++i) {
        sendNEC(SPEAKERS_HIGHER);
        delay(WAIT_TIME*4);
    }
}

void IRtransmitter::volume_up() {
    sendNEC(SPEAKERS_HIGHER);
}

void IRtransmitter::volume_down() {
    sendNEC(SPEAKERS_LOWER);
}

void IRtransmitter::up() {
    sendNEC(SPEAKERS_UP);
}

void IRtransmitter::down() {
    sendNEC(SPEAKERS_DOWN);
}

void IRtransmitter::menu() {
    sendNEC(SPEAKERS_MENU);
}

void IRtransmitter::select() {
    sendNEC(SPEAKERS_SELECT);
}

void IRtransmitter::playlist(int id) {
    for(int i = 0; i < 6; i++) {
        sendNEC(SPEAKERS_MENU);
        delay(WAIT_TIME);
    }
    for(int i = 0; i < 5; i++) {
        sendNEC(SPEAKERS_UP);
        delay(WAIT_TIME);
    }
    sendNEC(SPEAKERS_SELECT);
    delay(WAIT_TIME);
    for(int i = 0; i < 3; i++) {
        sendNEC(SPEAKERS_UP);
        delay(WAIT_TIME);
    }
    sendNEC(SPEAKERS_SELECT);
    delay(WAIT_TIME);
    for(int i = 0; i < 10; i++) {
        sendNEC(SPEAKERS_UP);
        delay(WAIT_TIME);
    }
    for(int i = 0; i < id; i++) {
        sendNEC(SPEAKERS_DOWN);
        delay(WAIT_TIME);
    }
    sendNEC(SPEAKERS_SELECT);
    delay(WAIT_TIME);
    sendNEC(SPEAKERS_SELECT);
}

void IRtransmitter::light_on() {
    sendRAW(VENT_LIGHT_ON);   
}

void IRtransmitter::light_off() {
    sendRAW(VENT_LIGHT_OFF);
}

void IRtransmitter::level_0() {
    sendRAW(VENT_LEVEL_0);
}

void IRtransmitter::level_3() {
    sendRAW(VENT_LEVEL_3);
}

long IRtransmitter::read() {
    long aux = -1;
    if (irrecv.decode(&results)) {
        aux = results.value;
        Serial.println(aux, HEX);
        irrecv.resume();
    }
    return aux;
}

void IRtransmitter::sendNEC(unsigned long ircode) {
    irsend.sendNEC(ircode, 32);
    delay(10);
    irrecv.enableIRIn();
}

void IRtransmitter::sendRAW(unsigned int (&ircode)[99]) {
    for(int i = 0; i < 3; i++) {
        irsend.sendRaw(ircode, 99 , 38);
        delay(10);
    }
    irrecv.enableIRIn();
}

bool IRtransmitter::isControllingSpeakers() const {
    return speakersControl;
}

void IRtransmitter::setControllingSpeakers(bool controlling) {
    speakersControl = controlling;
}
