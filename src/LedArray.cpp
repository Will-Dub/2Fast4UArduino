#include "LedArray.h"

void LedArray::setup() {
    pinMode(PIN_LED_1, OUTPUT);
    pinMode(PIN_LED_2, OUTPUT);
    pinMode(PIN_LED_3, OUTPUT);
    pinMode(PIN_LED_4, OUTPUT);
    pinMode(PIN_LED_5, OUTPUT);
    pinMode(PIN_LED_6, OUTPUT);
    pinMode(PIN_LED_7, OUTPUT);
    pinMode(PIN_LED_8, OUTPUT);
    pinMode(PIN_LED_9, OUTPUT);
    pinMode(PIN_LED_10, OUTPUT);
}

void LedArray::show(int value) {
    digitalWrite(PIN_LED_1, value >= 1 ? LOW : HIGH);
    digitalWrite(PIN_LED_2, value >= 2 ? LOW : HIGH);
    digitalWrite(PIN_LED_3, value >= 3 ? LOW : HIGH);
    digitalWrite(PIN_LED_4, value >= 4 ? LOW : HIGH);
    digitalWrite(PIN_LED_5, value >= 5 ? LOW : HIGH);
    digitalWrite(PIN_LED_6, value >= 6 ? LOW : HIGH);
    digitalWrite(PIN_LED_7, value >= 7 ? LOW : HIGH);
    digitalWrite(PIN_LED_8, value >= 8 ? LOW : HIGH);
    digitalWrite(PIN_LED_9, value >= 9 ? LOW : HIGH);
    digitalWrite(PIN_LED_10, value >= 10 ? LOW : HIGH);
}