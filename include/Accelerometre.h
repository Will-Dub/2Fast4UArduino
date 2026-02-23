#pragma once

#define ZERO_X 1.799
#define ZERO_Y 1.799
#define ZERO_Z 1.799
#define SENSITIVITY_X 0.4
#define SENSITIVITY_Y 0.4
#define SENSITIVITY_Z 0.4
#define ADC_REF 5

const int xInput= A2;
const int yInput= A1;
const int zInput= A0;

void lire_accelerometre();
float getXScaled();
float getYScaled();
float getAngle();