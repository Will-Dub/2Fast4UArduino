#include <Arduino.h>
#include "Accelerometre.h"
const int xInput= A1;
const int yInput= A7;
const int zInput= A5;

void lire_accelerometre()
{

int xRaw = analogRead(xInput);
int yRaw = analogRead(yInput);

float xScaled = (xRaw - 265) * 18.2 / 135 - 9.1;
float yScaled = (yRaw - 265) * 18.2 / 135 - 9.1;
float angle = atan2(xScaled,yScaled) * 180 / PI;
    if (9.7<=xScaled && yScaled==0) {
        angle=0; // Le volant est droit
    }
    if (xScaled==0 && yScaled<=-9.7) {
        angle=-90; // Le volant est tourné à gauche
    }
    if (xScaled==0 && yScaled>=9.7) {
        angle=90; // Le volant est tourné à droite
    }

    if (xScaled < 0 && yScaled <= 0) {
        angle=angle-90; // Ajuster l'angle pour le quadrant inférieur gauche
    }
    if (xScaled <= 0 && yScaled > 0) {
        angle=angle+90; // Ajuster l'angle pour le quadrant inferieur droit
    }


Serial.print("X, Y, Z :: ");
Serial.print(xScaled);
Serial.print(", ");
Serial.print(yScaled);
Serial.print(", ");
Serial.print(angle);
Serial.print("\n");


}
