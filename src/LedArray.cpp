#include "LedArray.h"


LedArray::LedArray(uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4,
                   uint8_t pin5, uint8_t pin6, uint8_t pin7, uint8_t pin8,
                   uint8_t pin9, uint8_t pin10)
{
    _pins[0] = pin1;
    _pins[1] = pin2;
    _pins[2] = pin3;
    _pins[3] = pin4;
    _pins[4] = pin5;
    _pins[5] = pin6;
    _pins[6] = pin7;
    _pins[7] = pin8;
    _pins[8] = pin9;
    _pins[9] = pin10;
}

void LedArray::begin()
{
    for(int i = 0; i < 10; i++) {
        pinMode(_pins[i], OUTPUT);
        digitalWrite(_pins[i], HIGH);
    }
}

void LedArray::show(int value)
{
    for(int i = 0; i < 10; i++) {
        digitalWrite(_pins[i], value >= i+1 ? LOW : HIGH);
    }
}