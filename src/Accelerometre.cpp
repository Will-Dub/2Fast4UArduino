#include <Arduino.h>
#include "Accelerometre.h"
#define ZERO_X 1.799
#define ZERO_Y 1.799
#define ZERO_Z 1.799
#define SENSITIVITY_X 0.4
#define SENSITIVITY_Y 0.4
#define SENSITIVITY_Z 0.4
#define ADC_REF 5

const int xInput= A5;
const int yInput= A3;
const int zInput= A1;
float xScaled;
float yScaled;
float angle;

void lire_accelerometre()
{
    int xRaw = analogRead(xInput);
    int yRaw = analogRead(yInput);

    /*unsigned int valueX = analogRead(SENSITIVITY_X);
    unsigned int valueY = analogRead(SENSITIVITY_Y);
    unsigned int valueZ = analogRead(SENSITIVITY_Z);

    float xv = (valueX/1024.0*ADC_REF-ZERO_X)/SENSITIVITY_X;
    float yv = (valueY/1024.0*ADC_REF-ZERO_Y)/SENSITIVITY_Y;
    float zv = (valueZ/1024.0*ADC_REF-ZERO_Y)/SENSITIVITY_Y;

    angle = atan2(-yv,-zv)*56.2957795+180;

    Serial.print(angle);*/

    xScaled = (xRaw - 265) * 18.2 / 135 - 9.1;
    yScaled = (yRaw - 265) * 18.2 / 135 - 9.1;
    float zScaled = (yRaw - 265) * 18.2 / 135 - 9.1;
    angle = atan2(xScaled,yScaled) * 180 / PI;
    if (9.7<=xScaled && yScaled==0) {
        angle=0; // Le volant est droit
        Serial.print("1");
    }
    if (xScaled==0 && yScaled<=-9.7) {
        angle=-90; // Le volant est tourné à gauche
    }
    if (xScaled==0 && yScaled>=9.7) {
        angle=90; // Le volant est tourné à droite
        Serial.print("2");
    }

    if (xScaled < 0 && yScaled <= 0) {
        // Haut gauche
        angle+=90;
        Serial.print("3");
    }
    if (xScaled <= 0 && yScaled > 0) {
        // Haut droit
        angle=angle+90;
        Serial.print("4");
    }
    if (xScaled > 0 && yScaled > 0) {
        // Bas droit
        angle=angle+90;
        Serial.print("5");
    }
    if (xScaled > 0 && yScaled <= 0) {
        // Bas gauche
        angle=angle-270;
        Serial.print("6");
    }


    Serial.print("X, Y, Z, angle :: ");
    Serial.print(xScaled);
    Serial.print(", ");
    Serial.print(yScaled);
    Serial.print(", ");
    Serial.print(zScaled);
    Serial.print(", ");
    Serial.print(angle);
    Serial.print("\n");


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