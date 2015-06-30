#include "Interruptor.h"
#include "Arduino.h"

Interruptor::Interruptor() {
    
}

void Interruptor::changeLight() {
    servo.attach(PIN_SERVO);
    int pos = servo.read();
    Serial.println(pos);
    int releasePos;
    if (pos <= pos1 + 30) {
        pos = pos2;
        releasePos = pos2 - 20;
    } else {
        pos = pos1;
        releasePos = pos1 + 20;
    }
    servo.write(pos);
    delay(200);
    servo.write(releasePos);
    delay(1000);
    changeLight();
    servo.detach();
}
