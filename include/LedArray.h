#pragma once
#include <Arduino.h>

class LedArray {
public:
    LedArray(uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4,
             uint8_t pin5, uint8_t pin6, uint8_t pin7, uint8_t pin8,
             uint8_t pin9, uint8_t pin10);

    void begin();
    void show(int value);

private:
    uint8_t _pins[10];
};