#include "DetecteurMuons.h"

DetecteurMuons::DetecteurMuons(int pin) {
    _pin = pin;
}

void DetecteurMuons::begin() {
    pinMode(_pin, INPUT);
}

int DetecteurMuons::lireValeur() {
    return analogRead(_pin);
}