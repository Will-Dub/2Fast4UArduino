#include <Arduino.h>
#include "EncodeurRotatif.h"
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
}

void EncodeurRotatif::update()
{
    statutCLK = digitalRead(clk);
    // Vérifier s'il y a eu un changement d'état sur CLK
    if (statutCLK != dernierCLK) {
        if (digitalRead(dt) != statutCLK) {
            counter++; // Rotation horaire
        } else {
            counter--; // Rotation antihoraire
        }
    }

    buttonPressed = (digitalRead(sw) == LOW);

    dernierCLK = statutCLK; // Mettre à jour le dernier statut de CLK
}

int EncodeurRotatif::getCounter() const
{
    return counter;
}

bool EncodeurRotatif::isPressed() const
{
    return buttonPressed;
}