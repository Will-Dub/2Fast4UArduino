#pragma once
#include <Arduino.h>

class EncodeurRotatif {
public:
        enum PositionCle {
        OFF = 0,
        ACC = 1,
        ON = 2,
        START = 3
    };

    EncodeurRotatif(uint8_t clk, uint8_t dt, uint8_t sw);

    void begin();
    void update();

    int getCounter() const;
    bool isPressed() const;
    bool isOn() const;
    void setOff() { counter = 0; etatOn = false; }
    void stall();   // force un calage moteur

private:
    uint8_t clk = 37;// Canal A (CLK) connecté à la broche numérique ...
    uint8_t dt = 35;// Canal de bouton (SW) connecté à la broche numérique ...
    uint8_t sw = 36;// Canal de bouton (SW) connecté à la broche numérique ...

    int dernierCLK;// Pour stocker le dernier état de CLK
    int statutCLK;// Pour stocker l'état actuel de CLK
    int counter = 0;// Suivre le nombre de rotations
    bool buttonPressed = false;// Suivre l'état du bouton
    bool etatOn = false;      // mémoire de l’état ON/OFF
    bool mustReturnToZero = false; // verrou après stall

};


