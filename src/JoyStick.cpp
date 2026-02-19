#include "JoyStick.h"


Joystick::Joystick(uint8_t pinX, uint8_t pinY, uint8_t pinBouton){
    this->pinX = pinX;
    this->pinY = pinY;
    this->pinBouton = pinBouton;

}

int Joystick::readX(){

    return analogRead(pinX);

}

int Joystick::readY(){

    return analogRead(pinY);

}


bool Joystick::readButton() {
    if (pinBouton == 255){ 
    return false;
    }

    return digitalRead(pinBouton) == LOW;
}




void Joystick::begin() {

    if (pinBouton != 255) {
    pinMode(pinBouton, INPUT_PULLUP);
    }

    pinMode(pinX, INPUT);
    pinMode(pinY, INPUT);
}


