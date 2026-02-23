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
float lastAccelAngle;

unsigned long lastLcdPrintTime;
unsigned long lastSeptSegPrintTime;
unsigned long lastAccelRotationTime;

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
    lastAccelRotationTime = millis();
}

void loop() {
//  writeSpeed(0,2,4);
//  writeSpeed(UNITS, TENS, HUNDREDS);
    encodeurUpdate();

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
            textToShowLine2 = "";
            break;
        case 2: //Module accéléromètre
            lire_accelerometre();
            textToShowLine1 = "X: ";
            textToShowLine1 += getXScaled();
            textToShowLine1 += " Y: ";
            textToShowLine1 += getYScaled();
            textToShowLine2 = "angle: ";
            textToShowLine2 += getAngle();
            break;
        case 4: //Horaire ou Antihoraire
            {
                // Lis chaque 200ms
                if(millis() < lastAccelRotationTime + 150){
                    break;
                }
                lastAccelRotationTime = millis();

                lire_accelerometre();
                float deltaAngle = getAngle() - lastAccelAngle;

                if(deltaAngle >= -2 && deltaAngle <= 2){
                    textToShowLine2 = "Aucun";
                }else if(deltaAngle < 0){
                    textToShowLine2 = "Antihoraire";
                }else{
                    textToShowLine2 = "Horaire";
                }

                textToShowLine1 = "Rotation: ";

                lastAccelAngle = getAngle();
                break;
            }
        default:
            textToShowLine1 = getCounter();
            textToShowLine1 += " n'est pas valide";
            textToShowLine2 = "";
            break;
    }
}