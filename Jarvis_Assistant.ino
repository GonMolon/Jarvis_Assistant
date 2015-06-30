#include "Jarvis.h"
#include <EasyVR.h>
#include <SoftwareSerial.h>
#include <IRremote.h>
#include <ServoTimer2.h>

Jarvis jarvis;

void setup() {
  Serial.begin(9600);
  jarvis.setup();
}

void loop() {
  jarvis.refresh();
}

