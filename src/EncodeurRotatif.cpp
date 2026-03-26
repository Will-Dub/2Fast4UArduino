#include <Arduino.h>
#include "EncodeurRotatif.h"

EncodeurRotatif::EncodeurRotatif(uint8_t clk, uint8_t dt, uint8_t sw)
{
    this->clk = clk;
    this->dt = dt;
    this->sw = sw;
}

void EncodeurRotatif::begin()
{
    pinMode(clk, INPUT_PULLUP);
    pinMode(dt, INPUT_PULLUP);
    pinMode(sw, INPUT_PULLUP);

    dernierCLK = digitalRead(clk);
    etatOn = false;
    counter = 0;
    mustReturnToZero = false;
}

void EncodeurRotatif::update()
{
    static unsigned long dernierTemps = 0;
    const unsigned long debounceDelay = 5;

    statutCLK = digitalRead(clk);

    // Détection d’un front descendant sur CLK
    if (dernierCLK == HIGH && statutCLK == LOW)
    {
        if (millis() - dernierTemps > debounceDelay)
        {
            // Sens de rotation
            if (digitalRead(dt) == HIGH)
            {
                // Tourne vers la droite
                if (counter < 3)
                {
                    counter++;
                }
            }
            else
            {
                // Tourne vers la gauche
                if (counter > 0)
                {
                    counter--;
                }
            }

            // Si le véhicule a calé, on oblige le retour à 0
            if (mustReturnToZero)
            {
                etatOn = false;

                if (counter == 0)
                {
                    mustReturnToZero = false; // clé revenue à la base
                }
            }
            else
            {
                // Fonctionnement normal
                if (counter == 0)
                {
                    etatOn = false;
                }
                else if (counter == 3)
                {
                    etatOn = true;
                }
            }

            dernierTemps = millis();
        }
    }

    buttonPressed = (digitalRead(sw) == LOW);
    dernierCLK = statutCLK;
}

int EncodeurRotatif::getCounter() const
{
    return counter;
}

bool EncodeurRotatif::isPressed() const
{
    return buttonPressed;
}

bool EncodeurRotatif::isOn() const
{
    return etatOn;
}

void EncodeurRotatif::stall()
{
    etatOn = false;
    mustReturnToZero = true;
}