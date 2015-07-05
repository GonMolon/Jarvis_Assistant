#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <SPI.h>
#include <Ethernet.h>

class HttpRequest {
private:
    IPAddress server = IPAddress(74,125,232,128); //google
    //IPAddress server(185,27,134,148); //bytehost
    IPAddress ip = IPAddress(192, 168, 1, 177);
    EthernetClient client;
    String result = "";
public:
    static const int REQUESTED = 1;
    static const int NOT_REQUESTED = 0;
    HttpRequest();
    bool GET(String query);
    unsigned long getTime();
    String getResult();
};

#endif // HTTPREQUEST_H
