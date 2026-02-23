#pragma once
#include <Arduino.h>

const int UNITS = 1;
const int TENS = 2;
const int HUNDREDS = 3;
const int SEGMENTS_PIN_A = 9;
const int SEGMENTS_PIN_B = 8;
const int SEGMENTS_PIN_C = 7;
const int SEGMENTS_PIN_D = 5;
const int SEGMENTS_PIN_E = 4;
const int SEGMENTS_PIN_F = 2;
const int SEGMENTS_PIN_G = 3;
const int SEGMENTS_ON_UNITS = 10;
const int SEGMENTS_ON_TENS = 11;
const int SEGMENTS_ON_HUNDREDS = 12;

void segmentsSetup();
void writeSpeed(int units, int tens, int hundreds);
void writeNumber(int number);
int getHundreds(float number);
int getTens(float number);
int getUnits(float number);

