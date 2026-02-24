#pragma once

class Pedale {
    private : 
         uint8_t PIN_PEDALE_1;

    public :
        Pedale (uint8_t PIN_PEDALE_1);
        float lirePourcentage();

};