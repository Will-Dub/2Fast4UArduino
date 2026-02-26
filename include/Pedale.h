#pragma once

class Pedale {
    private : 
         uint8_t m_pin;
         uint8_t m_maxValue;

    public :
        Pedale (uint8_t pin);
        float lirePourcentage();

};