#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

#define DEBOUNCE_MS 50


class Button {
public:
    void buttonBegin(uint8_t pin);
    uint8_t buttonRead();
    uint8_t get_lastState();

private:
    uint8_t _pin;
    uint8_t _lastState;
    unsigned long _lastTime;
};


#endif