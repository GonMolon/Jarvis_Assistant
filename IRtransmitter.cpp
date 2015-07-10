#include "IRtransmitter.h"

IRtransmitter::IRtransmitter() {
}

void IRtransmitter::setup() {
    irrecv.enableIRIn();
}

void IRtransmitter::start() {
    sendIR(SPEAKERS_ON);
    delay(200);
    play();
}

void IRtransmitter::play() {
    sendIR(SPEAKERS_PLAY);
}

void IRtransmitter::next() {
    sendIR(SPEAKERS_NEXT);
}


void IRtransmitter::previous() {
    sendIR(SPEAKERS_PREVIOUS);
}

void IRtransmitter::playlist(int id) {
    for(int i = 0; i < 6; i++) {
        sendIR(SPEAKERS_MENU);
    }
    for(int i = 0; i < 5; i++) {
        sendIR(SPEAKERS_UP);
    }
    sendIR(SPEAKERS_SELECT);
    delay(200);
    for(int i = 0; i < 3; i++) {
        sendIR(SPEAKERS_UP);
    }
    sendIR(SPEAKERS_SELECT);
    for(int i = 0; i < 10; i++) {
        sendIR(SPEAKERS_UP);
    }
    for(int i = 0; i < id; i++) {
        sendIR(SPEAKERS_DOWN);
    }
    sendIR(SPEAKERS_SELECT);
    sendIR(SPEAKERS_SELECT);
}

long IRtransmitter::read() {
    long aux = -1;
    if (irrecv.decode(&results)) {
        aux = this->results.value;
        Serial.println(aux, HEX);
        irrecv.resume();
    }
    return aux;
}


void IRtransmitter::sendIR(unsigned long ircode) {
    for(int i = 0; i < 1; i++) {
        irsend.sendNEC(ircode, 32);
        delay(10);
    }
    delay(200);
}

void IRtransmitter::sendIR(unsigned int (&ircode)[99]) {
    irsend.sendRaw(ircode, 99 , 38);
    delay(200);
}
