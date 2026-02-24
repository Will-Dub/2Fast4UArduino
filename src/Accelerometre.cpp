#include <Arduino.h>
#include "Accelerometre.h"

float xScaled;
float yScaled;
float angle;

void lire_accelerometre()
{
    int xRaw = analogRead(xInput);
    int yRaw = analogRead(yInput);

    xScaled = (xRaw - 265) * 19.62 / 135 - 9.81;
    yScaled = (yRaw - 265) * 19.62 / 135 - 9.81;

    angle = atan2(xScaled,yScaled) * 180 / PI;

    if (xScaled < 0 && yScaled <= 0) {
        // Haut gauche
        angle+=80;
    }
    if (xScaled <= 0 && yScaled > 0) {
        // Haut droit
        angle=angle+80;
    }
    if (xScaled > 0 && yScaled > 0) {
        // Bas droit
        angle=angle+80;
    }
    if (xScaled > 0 && yScaled <= 0) {
        // Bas gauche
        angle=angle-260;
    }
}

float getXScaled()
{
    return xScaled;
}

float getYScaled()
{
    return yScaled;
}

float getAngle()
{
    return angle;
}