#include "SeptSegments.h"

void segmentsSetup()
{
  pinMode(SEGMENTS_PIN_A, OUTPUT);
  pinMode(SEGMENTS_PIN_B, OUTPUT);
  pinMode(SEGMENTS_PIN_C, OUTPUT);
  pinMode(SEGMENTS_PIN_D, OUTPUT);
  pinMode(SEGMENTS_PIN_E, OUTPUT);
  pinMode(SEGMENTS_PIN_F, OUTPUT);
  pinMode(SEGMENTS_PIN_G, OUTPUT);

  digitalWrite(SEGMENTS_PIN_A, 1);
  digitalWrite(SEGMENTS_PIN_B, 1);
  digitalWrite(SEGMENTS_PIN_C, 1);
  digitalWrite(SEGMENTS_PIN_D, 1);
  digitalWrite(SEGMENTS_PIN_E, 1);
  digitalWrite(SEGMENTS_PIN_F, 1);
  digitalWrite(SEGMENTS_PIN_G, 1);
};

void writeSpeed(int units, int tens, int hundreds)
{
  digitalWrite(SEGMENTS_ON_UNITS, 1);
  writeNumber(units);
  delayMicroseconds(500);
  digitalWrite(SEGMENTS_ON_UNITS, 0);

  digitalWrite(SEGMENTS_ON_TENS, 1);
  writeNumber(tens);
  delayMicroseconds(500);
  digitalWrite(SEGMENTS_ON_TENS, 0);

  digitalWrite(SEGMENTS_ON_HUNDREDS, 1);
  writeNumber(hundreds);
  delayMicroseconds(500);
  digitalWrite(SEGMENTS_ON_HUNDREDS, 0);
};

void writeNumber(int number)
{
  switch (number)
  {
    case 0:
      digitalWrite(SEGMENTS_PIN_A, 0);
      digitalWrite(SEGMENTS_PIN_B, 0);
      digitalWrite(SEGMENTS_PIN_C, 0);
      digitalWrite(SEGMENTS_PIN_D, 0);
      digitalWrite(SEGMENTS_PIN_E, 0);
      digitalWrite(SEGMENTS_PIN_F, 0);
      digitalWrite(SEGMENTS_PIN_G, 1);
      break;
    case 1:
      digitalWrite(SEGMENTS_PIN_A, 1);
      digitalWrite(SEGMENTS_PIN_B, 0);
      digitalWrite(SEGMENTS_PIN_C, 0);
      digitalWrite(SEGMENTS_PIN_D, 1);
      digitalWrite(SEGMENTS_PIN_E, 1);
      digitalWrite(SEGMENTS_PIN_F, 1);
      digitalWrite(SEGMENTS_PIN_G, 1);
      break;
    case 2:
      digitalWrite(SEGMENTS_PIN_A, 0);
      digitalWrite(SEGMENTS_PIN_B, 0);
      digitalWrite(SEGMENTS_PIN_C, 1);
      digitalWrite(SEGMENTS_PIN_D, 0);
      digitalWrite(SEGMENTS_PIN_E, 0);
      digitalWrite(SEGMENTS_PIN_F, 1);
      digitalWrite(SEGMENTS_PIN_G, 0);
      break;
    case 3:
      digitalWrite(SEGMENTS_PIN_A, 0);
      digitalWrite(SEGMENTS_PIN_B, 0);
      digitalWrite(SEGMENTS_PIN_C, 0);
      digitalWrite(SEGMENTS_PIN_D, 0);
      digitalWrite(SEGMENTS_PIN_E, 1);
      digitalWrite(SEGMENTS_PIN_F, 1);
      digitalWrite(SEGMENTS_PIN_G, 0);
      break;
    case 4:
      digitalWrite(SEGMENTS_PIN_A, 1);
      digitalWrite(SEGMENTS_PIN_B, 0);
      digitalWrite(SEGMENTS_PIN_C, 0);
      digitalWrite(SEGMENTS_PIN_D, 1);
      digitalWrite(SEGMENTS_PIN_E, 1);
      digitalWrite(SEGMENTS_PIN_F, 0);
      digitalWrite(SEGMENTS_PIN_G, 0);
      break;
    case 5:
      digitalWrite(SEGMENTS_PIN_A, 0);
      digitalWrite(SEGMENTS_PIN_B, 1);
      digitalWrite(SEGMENTS_PIN_C, 0);
      digitalWrite(SEGMENTS_PIN_D, 0);
      digitalWrite(SEGMENTS_PIN_E, 1);
      digitalWrite(SEGMENTS_PIN_F, 0);
      digitalWrite(SEGMENTS_PIN_G, 0);
      break;
    case 6:
      digitalWrite(SEGMENTS_PIN_A, 0);
      digitalWrite(SEGMENTS_PIN_B, 1);
      digitalWrite(SEGMENTS_PIN_C, 0);
      digitalWrite(SEGMENTS_PIN_D, 0);
      digitalWrite(SEGMENTS_PIN_E, 0);
      digitalWrite(SEGMENTS_PIN_F, 0);
      digitalWrite(SEGMENTS_PIN_G, 0);
      break;
    case 7:
      digitalWrite(SEGMENTS_PIN_A, 0);
      digitalWrite(SEGMENTS_PIN_B, 0);
      digitalWrite(SEGMENTS_PIN_C, 0);
      digitalWrite(SEGMENTS_PIN_D, 1);
      digitalWrite(SEGMENTS_PIN_E, 1);
      digitalWrite(SEGMENTS_PIN_F, 1);
      digitalWrite(SEGMENTS_PIN_G, 1);
      break;
    case 8:
      digitalWrite(SEGMENTS_PIN_A, 0);
      digitalWrite(SEGMENTS_PIN_B, 0);
      digitalWrite(SEGMENTS_PIN_C, 0);
      digitalWrite(SEGMENTS_PIN_D, 0);
      digitalWrite(SEGMENTS_PIN_E, 0);
      digitalWrite(SEGMENTS_PIN_F, 0);
      digitalWrite(SEGMENTS_PIN_G, 0);
      break;
    case 9:
      digitalWrite(SEGMENTS_PIN_A, 0);
      digitalWrite(SEGMENTS_PIN_B, 0);
      digitalWrite(SEGMENTS_PIN_C, 0);
      digitalWrite(SEGMENTS_PIN_D, 0);
      digitalWrite(SEGMENTS_PIN_E, 1);
      digitalWrite(SEGMENTS_PIN_F, 0);
      digitalWrite(SEGMENTS_PIN_G, 0);
      break;
  };
};


int getHundreds(float number)
{
  int hundreds = number - ((int)number % 100);
    return hundreds;
}

int getTens(float number)
{
  int x = number - getHundreds(number)*100;
  int tens = x - x % 10;
    return tens;
}

int getUnits(float number)
{
  int units = number - getHundreds(number)*100 - getTens(number)*10;
    return units;
}


