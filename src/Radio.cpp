#include "Radio.h"
#include <CAN.h>

static volatile uint8_t timeH = 0;
static volatile uint8_t timeM = 0;
static volatile uint8_t timeS = 0;

static uint8_t keyState = 0x41;
static uint8_t lightsDriving = 0x02;
static uint8_t lightsDashIntensity = 0xC8;

static unsigned long lastRadioSend = 0;

// prototype interne
static void onCANReceive(int packetSize);

void Radio::radioSetup()
{
    CAN.setPins(10, 2);          // à adapter selon ton branchement
    CAN.setClockFrequency(16E6);  // à adapter selon ton module

    if (!CAN.begin(125E3))
    {
        Serial.println("Erreur CAN");
        while (1);
    }

    CAN.onReceive(onCANReceive);
}

void Radio::radioUpdate()
{
    static unsigned long lastTimeUpdate = 0;

    if (millis() - lastTimeUpdate >= 1000)
    {
        lastTimeUpdate = millis();

        timeS++;
        if (timeS > 59)
        {
            timeS = 0;
            timeM++;
            if (timeM > 59)
            {
                timeM = 0;
                timeH++;
                if (timeH > 23)
                {
                    timeH = 0;
                }
            }
        }
    }

    if (millis() - lastRadioSend >= 100)
    {
        lastRadioSend = millis();

        if (keyState != 0x00)
        {
            canSend(0x20B, keyState, 0x00, 0x00, 0x00, 0x00, 0x00);
            canSend(0x219, 3, 131, 0, 192, 16, 44, 8, 0);
            canSend(0x208, lightsDriving, lightsDashIntensity, 0x00, 0x00, 0x00, 0x00);
            canSend(0x3E6, timeH, timeM, timeS);
            canSend(0x3A3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
            canSend(0x21F, 0x01, 0x00, 0x50, 0x00, 0x00, 0x00, 0x00, 0x40);
        }
    }
}

void Radio::radioOn()
{
    keyState = 0x41;
    canSend(0x20B, keyState, 0x00, 0x00, 0x00, 0x00, 0x00);
}

void Radio::radioOff()
{
    keyState = 0x00;
    canSend(0x20B, keyState, 0x00, 0x00, 0x00, 0x00, 0x00);
}

void Radio::radioVolumeUp()
{
    canSend(0x3A3, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00);
    delay(50);
    canSend(0x3A3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
}

void Radio::radioVolumeDown()
{
    canSend(0x3A3, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00);
    delay(50);
    canSend(0x3A3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
}

void Radio::radioScanUp()
{
    canSend(0x3A3, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00);
    delay(50);
    canSend(0x3A3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
}

void Radio::radioScanDown()
{
    canSend(0x3A3, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00);
    delay(50);
    canSend(0x3A3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
}

void Radio::radioBand()
{
    canSend(0x3A3, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00);
    delay(50);
    canSend(0x3A3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
}

void Radio::radioPresetUp()
{
    canSend(0x3A3, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00);
    delay(50);
    canSend(0x3A3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
}

void Radio::radioPresetDown()
{
    canSend(0x3A3, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00);
    delay(50);
    canSend(0x3A3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
}

void Radio::radioSetTime(uint8_t h, uint8_t m, uint8_t s)
{
    timeH = h;
    timeM = m;
    timeS = s;
}

static void onCANReceive(int packetSize)
{
    uint32_t packetID = CAN.packetId();

    //Serial.print("Message radio recu ID = 0x");
    //Serial.println(packetID, HEX);

    while (CAN.available())
    {
        uint8_t b = CAN.read();
        //Serial.print("0x");
        //Serial.print(b, HEX);
        //Serial.print(" ");
    }
    //Serial.println();
}

void Radio::canSend(uint32_t ID, uint8_t b0)
{
    uint8_t b[1] = {b0};
    canTX(1, ID, b);
}

void Radio::canSend(uint32_t ID, uint8_t b0, uint8_t b1)
{
    uint8_t b[2] = {b0, b1};
    canTX(2, ID, b);
}

void Radio::canSend(uint32_t ID, uint8_t b0, uint8_t b1, uint8_t b2)
{
    uint8_t b[3] = {b0, b1, b2};
    canTX(3, ID, b);
}

void Radio::canSend(uint32_t ID, uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3)
{
    uint8_t b[4] = {b0, b1, b2, b3};
    canTX(4, ID, b);
}

void Radio::canSend(uint32_t ID, uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4)
{
    uint8_t b[5] = {b0, b1, b2, b3, b4};
    canTX(5, ID, b);
}

void Radio::canSend(uint32_t ID, uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4, uint8_t b5)
{
    uint8_t b[6] = {b0, b1, b2, b3, b4, b5};
    canTX(6, ID, b);
}

void Radio::canSend(uint32_t ID, uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4, uint8_t b5, uint8_t b6)
{
    uint8_t b[7] = {b0, b1, b2, b3, b4, b5, b6};
    canTX(7, ID, b);
}

void Radio::canSend(uint32_t ID, uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4, uint8_t b5, uint8_t b6, uint8_t b7)
{
    uint8_t b[8] = {b0, b1, b2, b3, b4, b5, b6, b7};
    canTX(8, ID, b);
}

void Radio::canTX(uint8_t packetSize, uint32_t ID, uint8_t b[])
{
    CAN.beginPacket(ID, packetSize);
    CAN.write(b, packetSize);
    CAN.endPacket();
}