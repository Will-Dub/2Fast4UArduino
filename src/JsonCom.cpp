#include "JsonCom.h"

JsonCom::JsonCom(HardwareSerial& serial, uint32_t baud)
: ser(serial), baudRate(baud) {}

void JsonCom::begin() {
    ser.begin(baudRate);
}

void JsonCom::sendJoy(unsigned long tMs, int x, int y, bool btn) {
    StaticJsonDocument<160> doc;
    doc["type"] = PacketType::JOYSTICK;
    doc["t"] = tMs;
    doc["x"] = x;
    doc["y"] = y;
    doc["b"] = btn;

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

void JsonCom::sendSteering(unsigned long tMs, float steering) {
    StaticJsonDocument<160> doc;
    doc["type"] = PacketType::STEERING;
    doc["t"] = tMs;
    doc["steering"] = steering;

    serializeJson(doc, ser);
    ser.println();
}

void JsonCom::sendStatus(unsigned long tMs, bool status){
    StaticJsonDocument<160> doc;
    doc["type"] = PacketType::STATUS;
    doc["t"] = tMs;
    doc["s"] = status;

    serializeJson(doc, ser);
    ser.println();
}

void JsonCom::sendMuon(unsigned long tMs){
    StaticJsonDocument<160> doc;
    doc["type"] = PacketType::MUON;
    doc["t"] = tMs;

    serializeJson(doc, ser);
    ser.println();
}

bool JsonCom::readInformation() {
    static char buffer[64]; 
    static size_t index = 0;

    while (ser.available() > 0) {
        char c = ser.read();

        if (c == '\n') {
            buffer[index] = '\0'; 
            
            StaticJsonDocument<64> doc;
            DeserializationError error = deserializeJson(doc, buffer);
            index = 0; 

            if (error) {
                return false; 
            } 
            // Met à jour les variables
            if (doc.containsKey("v")) m_vitesse = doc["v"].as<int>();
            if (doc.containsKey("r")) m_rpm = doc["r"].as<int>();
            if(doc.containsKey("s")) m_startedResetFlag = !doc["s"].as<bool>();
            return true;
        } 
        else if (index < sizeof(buffer) - 1) {
            buffer[index++] = c;
        }
    }

    return false; 
}

bool JsonCom::getStartedResetFlag(){
    if(m_startedResetFlag){
        m_startedResetFlag = false;
        return true;
    }
    return false;
}
