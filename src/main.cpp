#include <Arduino.h>
#include "SeptSegments.h"
#include "JoyStick.h"

Joystick js(A0, A1, 2);

void setup() {
    Serial.begin(115200);
    js.begin();
    segmentsSetup();
}

void loop() {
    writeSpeed(UNITS, TENS, HUNDREDS);

    int x = js.readX();
    int y = js.readY();
    bool button = js.readButton();

    Serial.print("X: ");
    Serial.print(x);
    Serial.print("   Y: ");
    Serial.print(y);
    Serial.print("   BTN: ");
    Serial.println(button);

    delay(100);
}