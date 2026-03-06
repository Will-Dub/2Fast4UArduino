#include "JsonCom.h"

JsonCom::JsonCom(HardwareSerial& serial, uint32_t baud)
: ser(serial), baudRate(baud) {}

void JsonCom::begin() {
    ser.begin(baudRate);
}

void JsonCom::sendJoy(unsigned long tMs, int mode, int x, int y, int btn) {
    StaticJsonDocument<160> doc;
    doc["type"] = PacketType::JOYSTICK;
    doc["t"] = tMs;
    doc["mode"] = mode;
    doc["x"] = x;
    doc["y"] = y;
    doc["btn"] = btn;

    serializeJson(doc, ser);
    ser.println();
}

void JsonCom::sendButtons(unsigned long tMs, int gas, int brake, int clutch) {
    StaticJsonDocument<160> doc;
    doc["type"] = PacketType::BUTTONS;
    doc["t"] = tMs;
    doc["g"] = gas;
    doc["b"] = brake;
    doc["c"] = clutch;

    serializeJson(doc, ser);
    ser.println();
}

void JsonCom::sendPedales(unsigned long tMs, float gas, float brake, float clutch){
    StaticJsonDocument<160> doc;
    doc["type"] = PacketType::PEDALES;
    doc["t"] = tMs;
    doc["g"] = gas;
    doc["b"] = brake;
    doc["c"] = clutch;

    serializeJson(doc, ser);
    ser.println();
}

void JsonCom::sendAccel(unsigned long tMs, float steering) {
    StaticJsonDocument<160> doc;
    doc["type"] = PacketType::ACCEL;
    doc["t"] = tMs;
    doc["steering"] = steering;

    serializeJson(doc, ser);
    ser.println();
}
