#include <EasyVR.h>
#include <SoftwareSerial.h>
#include <IRremote.h>
#include <Servo.h>
#include <SPI.h>
#include <Ethernet.h>
#include <dht11.h>
#include <Time.h>
#include "Jarvis.h"

Jarvis* jarvis;

void setup() {
  Serial.begin(9600);
  jarvis = new Jarvis();
}

void loop() {
  jarvis->refresh();
}

