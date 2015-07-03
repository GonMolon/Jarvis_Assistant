#include "Interruptor.h"
#include "Arduino.h"

Interruptor::Interruptor() {
    
}

void Interruptor::changeLight() {
    servo.attach(PIN_SERVO);
    int pos = servo.read();
    int releasePos;
    if (pos <= pos1 + 40) {
        pos = pos2;
        releasePos = pos2 - 20;
    } else {
        pos = pos1;
        releasePos = pos1 + 20;
    }
    for(int i = 0; i < 30; ++i) {
        servo.write(pos);
        delay(15);
    }
    servo.detach();
}
