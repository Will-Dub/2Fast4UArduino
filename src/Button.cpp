#include "Button.h"

uint8_t Button::get_lastState() {
    return _lastState;
}

void Button::buttonBegin(uint8_t pin) {
    _pin = pin;
    pinMode(_pin, INPUT);
    _lastState = 0;
    _lastTime = 0;
}

uint8_t Button::buttonRead() {
    uint8_t raw = !digitalRead(_pin); // INPUT_PULLUP: LOW = appuyé
    if (raw != _lastState && (millis() - _lastTime) > DEBOUNCE_MS) {
        _lastState = raw;
        _lastTime = millis();
    }
    return _lastState;
}
