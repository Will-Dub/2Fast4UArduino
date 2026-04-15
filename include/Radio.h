#pragma once
#include <Arduino.h>

class Radio
{
public:
    void radioSetup();
    void radioUpdate();

    void radioOn();
    void radioOff();

    void radioVolumeUp();
    void radioVolumeDown();

    void radioScanUp();
    void radioScanDown();

    void radioBand();
    void radioPresetUp();
    void radioPresetDown();

    void radioSetTime(uint8_t h, uint8_t m, uint8_t s = 0);

private:
    static void canTX(uint8_t packetSize, uint32_t ID, uint8_t b[]);

    static void canSend(uint32_t ID, uint8_t b0);
    static void canSend(uint32_t ID, uint8_t b0, uint8_t b1);
    static void canSend(uint32_t ID, uint8_t b0, uint8_t b1, uint8_t b2);
    static void canSend(uint32_t ID, uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3);
    static void canSend(uint32_t ID, uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4);
    static void canSend(uint32_t ID, uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4, uint8_t b5);
    static void canSend(uint32_t ID, uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4, uint8_t b5, uint8_t b6);
    static void canSend(uint32_t ID, uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4, uint8_t b5, uint8_t b6, uint8_t b7);
};