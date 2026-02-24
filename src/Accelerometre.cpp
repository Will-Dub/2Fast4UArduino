#include <Arduino.h>
#include "Accelerometre.h"

Accelerometre::Accelerometre(uint8_t xInput, uint8_t yInput, uint8_t zInput){
    this->xInput = xInput;
    this->yInput = yInput;
    this->zInput = zInput;
}

void Accelerometre:: lire_accelerometre()
{
    int xRaw = analogRead(xInput);
    int yRaw = analogRead(yInput);

    xScaled = (xRaw - 265) * 19.62 / 135 - 9.81;
    yScaled = (yRaw - 265) * 19.62 / 135 - 9.81;

    angle = atan2(xScaled,yScaled) * 180 / PI;

    if (xScaled < 0 && yScaled <= 0) {
        // Haut gauche
        angle+=90;
    }
    if (xScaled <= 0 && yScaled > 0) {
        // Haut droit
        angle=angle+90;
    }
    if (xScaled > 0 && yScaled > 0) {
        // Bas droit
        angle=angle+90;
    }
    if (xScaled > 0 && yScaled <= 0) {
        // Bas gauche
        angle=angle-270;
    }
}

float Accelerometre :: getXScaled()
{
    return xScaled;
}

float Accelerometre :: getYScaled()
{
    return yScaled;
}

float Accelerometre :: getAngle()
{
    return angle;
}