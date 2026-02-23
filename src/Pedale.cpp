#include <Arduino.h>
#include "Pedale.h"

float lirePourcentage(int pin) {
  int potValue = analogRead(pin);

  float percent = ((potValue - 76) * 3.16 / 1023.0) * 100.0;

  percent = constrain(percent, 0, 100);

  return percent;
}
