#pragma once
#include <Arduino.h>
#include <ArduinoJson.h>

class JsonCom {
public:
    enum PacketType : uint8_t {
        JOYSTICK = 0,
        BUTTONS = 1,
        PEDALES = 2,
        ACCEL = 3
    };

    explicit JsonCom(HardwareSerial& serial, uint32_t baudRate = 115200);

    void begin();

    // ---- Envoi ----
    void sendJoy(unsigned long tMs, int mode, int x, int y, int btn);
    void sendButtons(unsigned long tMs, int gas, int brake, int clutch);
    void sendPedales(unsigned long tMs, float gas, float brake, float clutch);
    void sendAccel(unsigned long tMs, float steering);
private:
    HardwareSerial& ser;
    uint32_t baudRate;
};