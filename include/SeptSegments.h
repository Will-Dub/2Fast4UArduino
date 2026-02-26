#pragma once
#include <Arduino.h>

class SeptSegments {
public:
    // Constructeur
    SeptSegments(uint8_t pinA, uint8_t pinB, uint8_t pinC,
                 uint8_t pinD, uint8_t pinE, uint8_t pinF, uint8_t pinG,
                 uint8_t pinUnits, uint8_t pinTens, uint8_t pinHundreds);

    // Initialise les pins
    void begin();

    void writeNumber(int number);

    void writeDigits(int units, int tens, int hundreds);

    // Getters 
    int getUnits(int number) const;
    int getTens(int number) const;
    int getHundreds(int number) const;

private:

    uint8_t _pinA, _pinB, _pinC, _pinD, _pinE, _pinF, _pinG;
    uint8_t _pinUnits, _pinTens, _pinHundreds;

    // Allume/éteint les segments pour un chiffre 0..9
    void setSegmentsForDigit(uint8_t digit);

    // Active un digit (unités/dizaines/centaines)
    void enableUnits();
    void enableTens();
    void enableHundreds();
    void disableAllDigits();
};
