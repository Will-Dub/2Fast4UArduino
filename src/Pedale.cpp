#include <Arduino.h>
#include "Pedale.h"

Pedale::Pedale(uint8_t PIN_PEDALE_1){
  this->PIN_PEDALE_1 = PIN_PEDALE_1;
}

float Pedale::lirePourcentage() {
  int potValue = analogRead(PIN_PEDALE_1);

  float percent = (potValue - 656) * 100.0 / (945.0 - 656.0);
  percent = constrain(percent, 0, 100);

  if (percent < 0.5) percent = 0;

  return percent;
}
