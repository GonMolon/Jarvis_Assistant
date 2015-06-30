#include "IRtransmitter.h"

IRtransmitter::IRtransmitter() {
}

void IRtransmitter::setup() {
    irrecv.enableIRIn();
}

void IRtransmitter::start() {
    sendIR(ENCENDER);
    delay(200);
    play();
}

void IRtransmitter::play() {
    sendIR(PLAY);
}

void IRtransmitter::next() {
    sendIR(NEXT);
}


void IRtransmitter::previous() {
    sendIR(PREVIOUS);
}

void IRtransmitter::playlist(int id) {
    for(int i = 0; i < 6; i++) {
        sendIR(MENU);
    }
    for(int i = 0; i < 5; i++) {
        sendIR(UP);
    }
    sendIR(SELECT);
    delay(200);
    for(int i = 0; i < 3; i++) {
        sendIR(UP);
    }
    sendIR(SELECT);
    for(int i = 0; i < 10; i++) {
        sendIR(UP);
    }
    for(int i = 0; i < id; i++) {
        sendIR(DOWN);
    }
    sendIR(SELECT);
    sendIR(SELECT);
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
