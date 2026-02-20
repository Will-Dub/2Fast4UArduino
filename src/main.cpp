#include <Arduino.h>
#include <LiquidCrystal.h>
#include "SeptSegments.h"
#include "JoyStick.h"
#include "LedArray.h"
#include "Encodeur_rotatif.h"

Joystick js(A0, A1, 2);
LedArray ledArray;
LiquidCrystal lcd(43,42,41,40,39,38);

void setup() {
    Serial.begin(115200);
    js.begin();
    segmentsSetup();
    ledArray.setup();
    lcd.begin(16, 2);
    Encodeur_init();
}

void loop() {
    writeSpeed(0,2,4);
    lcd.clear();
    writeSpeed(UNITS, TENS, HUNDREDS);
    Encodeur_update();

    char numChar[10] = {};

    itoa(getCounter(), numChar, 10);

    lcd.write(numChar);
    Serial.print(numChar);
    delay(1);
}