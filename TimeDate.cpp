#include "TimeDate.h"
#include "HttpRequest.h"
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>

TimeDate::TimeDate() {
    
}

int TimeDate::getHour() {
    return hour; 
}

int TimeDate::getMin() {
    return min; 
}

int TimeDate::getDay() {
    return day; 
}

int TimeDate::getMonth() {
    return month; 
}

int TimeDate::getYear() {
    return year; 
}

void TimeDate::setMilliseconds(unsigned long milli) {
    hour = (milli  % 86400L) / 3600;
    min = (milli  % 3600) / 60;
}

void TimeDate::refresh() {
    HttpRequest request;
    setMilliseconds(request.getTime());
}


