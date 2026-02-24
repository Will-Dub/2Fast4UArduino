#include "JsonCom.h"

JsonCom::JsonCom(HardwareSerial& serial, uint32_t baud)
: ser(serial), baudRate(baud) {}

void JsonCom::begin() {
    ser.begin(baudRate);
}

void JsonCom::sendJoy(unsigned long tMs, int mode, int x, int y, int btn) {
    StaticJsonDocument<160> doc;
    doc["type"] = "joy";
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
    doc["type"] = "buttons";
    doc["t"] = tMs;
    doc["gas"] = gas;
    doc["brake"] = brake;
    doc["clutch"] = clutch;

    serializeJson(doc, ser);
    ser.println();
}

void JsonCom::sendAccel(unsigned long tMs, float x, float y, float angle) {
    StaticJsonDocument<160> doc;
    doc["type"] = "accel";
    doc["t"] = tMs;
    doc["x"] = x;
    doc["y"] = y;
    doc["angle"] = angle;

    serializeJson(doc, ser);
    ser.println();
}
