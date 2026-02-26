#include <Arduino.h>
#include "Pedale.h"

Pedale::Pedale(uint8_t pin){
  m_pin = pin;
}

float Pedale::lirePourcentage() {
  int potValue = analogRead(m_pin);

  float percent = ((potValue - 77) * 3.16 / 1023.0) * 100.0;

  if(percent < 0.5) percent = 0;
  if(percent > 100) percent = 100;

  return percent;
}
