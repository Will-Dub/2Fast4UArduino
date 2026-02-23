#include <Arduino.h>
#include "Pedale.h"

float lirePourcentage() {
  int potValue = analogRead(PIN_PEDALE_1);

  float percent = ((potValue - 76) * 3.16 / 1023.0) * 100.0;

  percent = constrain(percent, 0, 100);

  return percent;
}
