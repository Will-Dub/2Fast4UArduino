#pragma once
#include <Arduino.h>
#include <ArduinoJson.h>

class JsonCom {
public:
    enum PacketType : uint8_t {
        JOYSTICK = 0,
        BUTTONS = 1,
        PEDALES = 2,
        STEERING = 3
    };

    explicit JsonCom(HardwareSerial& serial, uint32_t baudRate = 115200);

    void begin();

    // ---- Envoi ----
    void sendJoy(unsigned long tMs, int x, int y, bool btn);
    void sendButtons(unsigned long tMs, int gas, int brake, int clutch);
    void sendPedales(unsigned long tMs, float gas, float brake, float clutch);
    void sendSteering(unsigned long tMs, float steering);

    // Recois
    bool readInformation();

    int getVitesse() const { return m_vitesse; }
    int getRpm() const { return m_rpm; }
    int getEtat() const { return m_etat;}
    int setEtat(int etat);

private:
    HardwareSerial& ser;
    uint32_t baudRate;

    int m_vitesse = 0;
    int m_rpm = 0;
    int m_etat = 1;
};