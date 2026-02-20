#include <Arduino.h>
#include "SeptSegments.h"
#include "JoyStick.h"
#include "LedArray.h"

Joystick js(A0, A1, 2);
LedArray ledArray;

void setup() {
    Serial.begin(115200);
    js.begin();
    segmentsSetup();
    ledArray.setup();
}

void loop() {
    writeSpeed(0,2,4);

    int x = js.readX();
    int y = js.readY();
    bool button = js.readButton();

    Serial.print("X: ");
    Serial.print(x);
    Serial.print("   Y: ");
    Serial.print(y);
    Serial.print("   BTN: ");
    Serial.println(button);
}