#ifndef DATABASE_H
#define DATABASE_H

#include <EEPROM.h>

class Database {
public:
    static const int INTERNET = 0;
    static const int OPERATION = 1;
    static const int MILLI = 2;
    
    static void reset();
    static int read_int(int pos);
    static void write_int(int pos, int value);
    static long read_long(int pos);
    static void write_long(int pos, unsigned long value);
};

#endif // DATABASE_H
