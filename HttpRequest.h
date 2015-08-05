#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <SPI.h>
#include <Ethernet.h>

class HttpRequest {
private:
public:
    HttpRequest();
    bool GET(String query);
    unsigned long getTime(int timeZone);
};

#endif // HTTPREQUEST_H
