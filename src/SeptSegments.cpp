#include "SeptSegments.h"

// --------- Constructeur ----------
SeptSegments::SeptSegments(uint8_t pinA, uint8_t pinB, uint8_t pinC,
                           uint8_t pinD, uint8_t pinE, uint8_t pinF, uint8_t pinG,
                           uint8_t pinUnits, uint8_t pinTens, uint8_t pinHundreds)
{
    _pinA = pinA; _pinB = pinB; _pinC = pinC;
    _pinD = pinD; _pinE = pinE; _pinF = pinF; _pinG = pinG;

    _pinUnits = pinUnits;
    _pinTens = pinTens;
    _pinHundreds = pinHundreds;
}

// --------- Init ----------
void SeptSegments::begin()
{
    pinMode(_pinA, OUTPUT);
    pinMode(_pinB, OUTPUT);
    pinMode(_pinC, OUTPUT);
    pinMode(_pinD, OUTPUT);
    pinMode(_pinE, OUTPUT);
    pinMode(_pinF, OUTPUT);
    pinMode(_pinG, OUTPUT);

    pinMode(_pinUnits, OUTPUT);
    pinMode(_pinTens, OUTPUT);
    pinMode(_pinHundreds, OUTPUT);

    // Tout éteindre au départ
    disableAllDigits();
    digitalWrite(_pinA, HIGH);
    digitalWrite(_pinB, HIGH);
    digitalWrite(_pinC, HIGH);
    digitalWrite(_pinD, HIGH);
    digitalWrite(_pinE, HIGH);
    digitalWrite(_pinF, HIGH);
    digitalWrite(_pinG, HIGH);
}

// --------- Affichage ----------
void SeptSegments::writeNumber(int number)
{
    // On limite 0..999 
    if (number < 0) number = 0;
    if (number > 999) number = 999;

    int h = getHundreds(number);
    int t = getTens(number);
    int u = getUnits(number);

    writeDigits(u, t, h);
}

void SeptSegments::writeDigits(int units, int tens, int hundreds)
{
    //  on affiche chaque digit très vite l’un après l’autre.
    disableAllDigits();

    enableUnits();
    setSegmentsForDigit(units);
    delayMicroseconds(400);
    disableAllDigits();

    enableTens();
    setSegmentsForDigit(tens);
    delayMicroseconds(400);
    disableAllDigits();

    enableHundreds();
    setSegmentsForDigit(hundreds);
    delayMicroseconds(400);
    disableAllDigits();
}

// --------- digits ----------
int SeptSegments::getHundreds(int number) const
{
    return number / 100;
}

int SeptSegments::getTens(int number) const
{
    return (number - getHundreds(number) * 100) / 10;
}

int SeptSegments::getUnits(int number) const
{
    return number - getHundreds(number) * 100 - getTens(number) * 10;
}

// --------- Contrôle digits ----------
void SeptSegments::enableUnits()
{
    digitalWrite(_pinUnits, HIGH);
    digitalWrite(_pinTens, LOW);
    digitalWrite(_pinHundreds, LOW);
}

void SeptSegments::enableTens()
{
    digitalWrite(_pinUnits, LOW);
    digitalWrite(_pinTens, HIGH);
    digitalWrite(_pinHundreds, LOW);
}

void SeptSegments::enableHundreds()
{
    digitalWrite(_pinUnits, LOW);
    digitalWrite(_pinTens, LOW);
    digitalWrite(_pinHundreds, HIGH);
}

void SeptSegments::disableAllDigits()
{
    digitalWrite(_pinUnits, LOW);
    digitalWrite(_pinTens, LOW);
    digitalWrite(_pinHundreds, LOW);
}

// --------- Mapping segments ----------
void SeptSegments::setSegmentsForDigit(uint8_t digit)
{
    switch (digit)
    {
        case 0:
            digitalWrite(_pinA, LOW);
            digitalWrite(_pinB, LOW);
            digitalWrite(_pinC, LOW);
            digitalWrite(_pinD, LOW);
            digitalWrite(_pinE, LOW);
            digitalWrite(_pinF, LOW);
            digitalWrite(_pinG, HIGH);
            break;

        case 1:
            digitalWrite(_pinA, HIGH);
            digitalWrite(_pinB, LOW);
            digitalWrite(_pinC, LOW);
            digitalWrite(_pinD, HIGH);
            digitalWrite(_pinE, HIGH);
            digitalWrite(_pinF, HIGH);
            digitalWrite(_pinG, HIGH);
            break;

        case 2:
            digitalWrite(_pinA, LOW);
            digitalWrite(_pinB, LOW);
            digitalWrite(_pinC, HIGH);
            digitalWrite(_pinD, LOW);
            digitalWrite(_pinE, LOW);
            digitalWrite(_pinF, HIGH);
            digitalWrite(_pinG, LOW);
            break;

        case 3:
            digitalWrite(_pinA, LOW);
            digitalWrite(_pinB, LOW);
            digitalWrite(_pinC, LOW);
            digitalWrite(_pinD, LOW);
            digitalWrite(_pinE, HIGH);
            digitalWrite(_pinF, HIGH);
            digitalWrite(_pinG, LOW);
            break;

        case 4:
            digitalWrite(_pinA, HIGH);
            digitalWrite(_pinB, LOW);
            digitalWrite(_pinC, LOW);
            digitalWrite(_pinD, HIGH);
            digitalWrite(_pinE, HIGH);
            digitalWrite(_pinF, LOW);
            digitalWrite(_pinG, LOW);
            break;

        case 5:
            digitalWrite(_pinA, LOW);
            digitalWrite(_pinB, HIGH);
            digitalWrite(_pinC, LOW);
            digitalWrite(_pinD, LOW);
            digitalWrite(_pinE, HIGH);
            digitalWrite(_pinF, LOW);
            digitalWrite(_pinG, LOW);
            break;

        case 6:
            digitalWrite(_pinA, LOW);
            digitalWrite(_pinB, HIGH);
            digitalWrite(_pinC, LOW);
            digitalWrite(_pinD, LOW);
            digitalWrite(_pinE, LOW);
            digitalWrite(_pinF, LOW);
            digitalWrite(_pinG, LOW);
            break;

        case 7:
            digitalWrite(_pinA, LOW);
            digitalWrite(_pinB, LOW);
            digitalWrite(_pinC, LOW);
            digitalWrite(_pinD, HIGH);
            digitalWrite(_pinE, HIGH);
            digitalWrite(_pinF, HIGH);
            digitalWrite(_pinG, HIGH);
            break;

        case 8:
            digitalWrite(_pinA, LOW);
            digitalWrite(_pinB, LOW);
            digitalWrite(_pinC, LOW);
            digitalWrite(_pinD, LOW);
            digitalWrite(_pinE, LOW);
            digitalWrite(_pinF, LOW);
            digitalWrite(_pinG, LOW);
            break;

        case 9:
            digitalWrite(_pinA, LOW);
            digitalWrite(_pinB, LOW);
            digitalWrite(_pinC, LOW);
            digitalWrite(_pinD, LOW);
            digitalWrite(_pinE, HIGH);
            digitalWrite(_pinF, LOW);
            digitalWrite(_pinG, LOW);
            break;

        default:
            // Si on reçoit un chiffre hors 0..9 : tout éteindre
            digitalWrite(_pinA, HIGH);
            digitalWrite(_pinB, HIGH);
            digitalWrite(_pinC, HIGH);
            digitalWrite(_pinD, HIGH);
            digitalWrite(_pinE, HIGH);
            digitalWrite(_pinF, HIGH);
            digitalWrite(_pinG, HIGH);
            break;
    }
}