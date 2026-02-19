#include <Arduino.h>
#include "Accelerometre.h"
const int xInput= A1;
const int yInput= A7;
const int zInput= A5;




const int sampleSize = 10;





void lire_accelerometre()
{

int xRaw = analogRead(xInput);
int yRaw = analogRead(yInput);



float xScaled = (xRaw - 265) * 18.2 / 135 - 9.1;
float yScaled = (yRaw - 265) * 18.2 / 135 - 9.1;





Serial.print("X, Y, Z :: ");
Serial.print(xScaled);
Serial.print(", ");
Serial.print(yScaled);

Serial.print("\n");


}
