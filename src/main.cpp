#include <Arduino.h>
#include <LiquidCrystal.h>
#include <string.h>
#include "SeptSegments.h"
#include "JoyStick.h"
#include "LedArray.h"
#include "EncodeurRotatif.h"
#include "Accelerometre.h"
#include "Button.h"

Joystick js(A0, A1, 2);
LedArray ledArray;
LiquidCrystal lcd(43,42,41,40,39,38);
Button bouton1;
String textToShowLine1;
String textToShowLine2;
int septSegUnits;
int septSegTens;
int septSegHundreds;

unsigned long lastLcdPrintTime;
unsigned long lastSeptSegPrintTime;

void setup() {
    Serial.begin(115200);
    js.begin();
    segmentsSetup();
    ledArray.setup();
    lcd.begin(16, 2);
    encodeurInit();
    bouton1.buttonBegin(34);

    lastLcdPrintTime = millis();
    lastSeptSegPrintTime = millis();
}

void loop() {
//  writeSpeed(0,2,4);
//  writeSpeed(UNITS, TENS, HUNDREDS);
    encodeurUpdate();

    char numChar[10] = {};

    itoa(getCounter(), numChar, 10);

   // Serial.print(numChar);

    if(millis() >= lastLcdPrintTime + 100){
        lcd.clear();
        lcd.print(textToShowLine1);
        lcd.setCursor(0,1);
        lcd.print(textToShowLine2);
        lastLcdPrintTime = millis();
    }

    if(millis() >= lastSeptSegPrintTime + 10){
        writeSpeed(septSegUnits, septSegTens, septSegHundreds);
        lastSeptSegPrintTime = millis();
    }

    switch (getCounter())
    {
        case 0: //État des boutons
            textToShowLine1 = bouton1.buttonRead() ? "Appuye" : "Non appuye";
            break;
        case 2: //Module accéléromètre
            lire_accelerometre();
            /*char xChar[10] = {};
            ltoa(getXScaled(), xChar, 10);
            char yChar[10] = {};
            ltoa(getYScaled(), xChar, 10);
            char angleChar[10] = {};
            ltoa(getAngle(), xChar, 10); */
            textToShowLine1 = "X: ";
            textToShowLine1 += getXScaled();
            textToShowLine1 += " Y: ";
            textToShowLine1 += getYScaled();
            textToShowLine2 = "angle: ";
            textToShowLine2 += getAngle();
            Serial.print("Angle: ");
            Serial.print(getAngle());
            Serial.print("\n");
            break;
        case 4: //Horaire ou Antihoraire

        default:
            textToShowLine1 = getCounter();
            textToShowLine1 += " n'est pas valide";
            break;
    }

    delay(10);


    

}