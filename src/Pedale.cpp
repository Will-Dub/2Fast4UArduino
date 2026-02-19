
#include "Pedale.h"

const int potPin = A0;

float lirePourcentage(int pin) {
  int potValue = analogRead(pin);

  float percent = ((potValue - 76) * 3.16 / 1023.0) * 100.0;

  percent = constrain(percent, 0, 100);

  return percent;
}

// void setup() {
//   Serial.begin(9600);
// }

// void loop() {

//   float percent = lirePourcentage(potPin);

//   Serial.print("Pourcentage: ");
//   Serial.print(percent);
//   Serial.println(" %");

//   delay(200);
// }
