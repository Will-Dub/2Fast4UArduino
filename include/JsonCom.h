#pragma once
#include <Arduino.h>
#include <ArduinoJson.h>

class JsonCom {
public:
    explicit JsonCom(HardwareSerial& serial, uint32_t baudRate = 115200);

    void begin();

    // ---- Envoi ----
    void sendJoy(unsigned long tMs, int mode, int x, int y, int btn);
    void sendButtons(unsigned long tMs, int gas, int brake, int clutch);
    void sendAccel(unsigned long tMs, float x, float y, float angle);
private:
    HardwareSerial& ser;
    uint32_t baudRate;
};