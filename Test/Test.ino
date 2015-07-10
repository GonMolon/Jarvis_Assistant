#include <IRremote.h>

IRsend irsend;

unsigned int raw[] = {500, 700, 500, 700, 450, 1600, 500, 1600, 450, 1650, 450, 1600, 550, 1550, 450, 750, 500, 1550, 500, 1600, 450, 1600, 550, 650, 550, 4500, 550, 650, 450, 700, 550, 1550, 500, 1600, 450, 1600, 550, 1550, 450, 1600, 550, 650, 500, 1600, 500, 1600, 450, 1600, 550, 650, 500, 4550, 500, 650, 550, 650, 550, 1550, 450, 1600, 500, 1600, 500, 1600, 500, 1550, 550, 650, 500, 1600, 450, 1600, 500, 1600, 500, 700, 450, 4700, 500, 700, 450, 700, 500, 1600, 500, 1600, 500, 1550, 550, 1550, 500, 1550, 500, 700, 550, 1550, 500, 1550, 550};

void setup() {
}

void loop() {
    irsend.sendRaw(raw, 99, 38);
    delay(3000);
}