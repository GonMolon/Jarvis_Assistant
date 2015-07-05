#include <EasyVR.h>
#include <SoftwareSerial.h>
#include <IRremote.h>
#include <Servo.h>
#include <SPI.h>
#include <Ethernet.h>
#include <EEPROM.h>

#include "Jarvis.h"
#include "HttpRequest.h"
#include "Database.h"

Jarvis jarvis;

void setup() {
  Serial.begin(9600);
  jarvis.setup();
}

void loop() {
  jarvis.refresh();
}

