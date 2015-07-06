#include "HttpRequest.h"

HttpRequest::HttpRequest() {
  
}

unsigned long HttpRequest::getTime() {
  byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
  unsigned int localPort = 8888;       // local port to listen for UDP packets
  char timeServer[] = "time.nist.gov"; // time.nist.gov NTP server
  const int NTP_PACKET_SIZE = 48; // NTP time stamp is in the first 48 bytes of the message
  byte packetBuffer[ NTP_PACKET_SIZE]; //buffer to hold incoming and outgoing packets
  EthernetUDP Udp;
  Ethernet.begin(mac, ip);
  Udp.begin(localPort);
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  packetBuffer[0] = 0b11100011;
  packetBuffer[1] = 0;
  packetBuffer[2] = 6;
  packetBuffer[3] = 0xEC;
  packetBuffer[12] = 49;
  packetBuffer[13] = 0x4E;
  packetBuffer[14] = 49;
  packetBuffer[15] = 52;
  Udp.beginPacket(timeServer, 123);
  Udp.write(packetBuffer, NTP_PACKET_SIZE);
  Udp.endPacket();
  delay(1000);
  if ( Udp.parsePacket() ) {
    Udp.read(packetBuffer, NTP_PACKET_SIZE);
    unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
    unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
    unsigned long secsSince1900 = highWord << 16 | lowWord;
    const unsigned long seventyYears = 2208988800UL;
    unsigned long milis = secsSince1900 - seventyYears - 3600*2*1000;
    Udp.stop();
    return milis;
  } else {
    return -1;
  }
}

bool HttpRequest::GET(String query) {
  bool error = false;
  byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
  Ethernet.begin(mac, ip);
  delay(1000);
  Serial.println("connecting...");
  if (client.connect(server, 80)) {
    Serial.println("connected");
    client.println("GET " + query);
    client.println("Connection: close");
    client.println();
  }
  else {
    Serial.println("connection failed");
    error = true;
  }
  while(client.connected()) {
    if(client.available()) {
      char c = client.read();
      Serial.print(c);
      result = result + c;
    }
    delay(25);
  }
  client.stop();
  return error;
}

String HttpRequest::getResult() {
  return result;
}

