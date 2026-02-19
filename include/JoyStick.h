#pragma once
#include <Arduino.h>

class Joystick {
public:
    Joystick(); // Constructeur par défault des fois que Will fasse le con
    Joystick(uint8_t pinX, uint8_t pinY, uint8_t pinBouton = 255);

    void begin();

    int readX();
    int readY();
    bool readButton();

private:
    uint8_t pinX;
    uint8_t pinY; 
    uint8_t pinBouton; 
};