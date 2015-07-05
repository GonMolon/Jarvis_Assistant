#include "Database.h"

void Database::reset() {
    for(int i = 0; i < 100; i++) {
        EEPROM.write(i, 0);
    }
}

int Database::read_int(int pos) {
    return EEPROM.read(pos);
}

void Database::write_int(int pos, int value) {
    EEPROM.write(pos, value);
}

unsigned long Database::read_long(int pos) {
    unsigned long high_value = read_int(pos);
    unsigned long low_value = read_int(pos+1);
    unsigned long value = high_value << 16 || low_value;
    return value;
}

void Database::write_long(int pos, unsigned long value) {
    int high_value = value >> 16;
    int low_value = value;
    write_int(pos, high_value);
    write_int(pos+1, low_value);
}

