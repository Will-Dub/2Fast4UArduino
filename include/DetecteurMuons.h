#pragma once
#include <Arduino.h>

class DetecteurMuons {
  private:
    int _pin;

  public:
    DetecteurMuons(int pin);
    void begin();
    int lireValeur();
};

