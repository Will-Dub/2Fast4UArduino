#pragma once
#include <Arduino.h>

#define PIN_LED_1 53
#define PIN_LED_2 52
#define PIN_LED_3 51
#define PIN_LED_4 50
#define PIN_LED_5 49
#define PIN_LED_6 48
#define PIN_LED_7 47
#define PIN_LED_8 46
#define PIN_LED_9 45
#define PIN_LED_10 44

class LedArray {
public:
    LedArray() {}
    void setup();
    void show(int value);
};