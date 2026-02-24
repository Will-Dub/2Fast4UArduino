#pragma once

class Accelerometre {

    public :
        Accelerometre(uint8_t xInput, uint8_t yInput, uint8_t zInput);
        void lire_accelerometre();
        float getXScaled();
        float getYScaled();
        float getAngle();

    private : 
        uint8_t xInput;
        uint8_t yInput;
        uint8_t zInput;
        float xScaled = 0.0f;
        float yScaled = 0.0f;
        float angle   = 0.0f;
};