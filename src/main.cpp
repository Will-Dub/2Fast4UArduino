#include <Arduino.h>
#include <LiquidCrystal.h>
#include <string.h>
#include "SeptSegments.h"
#include "JoyStick.h"
#include "LedArray.h"
#include "EncodeurRotatif.h"
#include "Accelerometre.h"
#include "Button.h"
#include "Pedale.h"
#include "JsonCom.h"


EncodeurRotatif encodeur(37,36,35); 
SeptSegments septSeg(9,8,7,5,4,2,3, 10,11,12); 
LedArray ledArray(53,52,51,50,49,48,47,46,45,44); 
Pedale pedaleAccel (A6);
Pedale pedaleBrake (A7);
Pedale pedaleGearShift (A5);
Joystick js(A8, A9, 33);
LiquidCrystal lcd(43,42,41,40,39,38);
Accelerometre accelerometre(A2,A1,A0);
Button bouton1;
Button bouton2;
Button bouton3;
JsonCom jsonCom(Serial);
String textToShowLine1;
String textToShowLine2;


int septSegUnits;
int septSegTens;
int septSegHundreds;
float lastAccelAngle;

unsigned long lastLcdPrintTime;
unsigned long lastSeptSegPrintTime;
unsigned long lastInformationSendTime;
unsigned long lastInformationReadTime;
bool wasOn = false;

void setup() {
    js.begin();
    encodeur.begin(); 
    septSeg.begin(); 
    ledArray.begin(); 
    lcd.begin(16, 2);
    bouton1.buttonBegin(34);
    bouton2.buttonBegin(A14);
    bouton3.buttonBegin(32);

    lastLcdPrintTime = millis();
    lastSeptSegPrintTime = millis();
    lastInformationSendTime = millis();
    lastInformationReadTime = millis();
    jsonCom.begin();

    ledArray.show(10);
}

void loop() {
    encodeur.update();

    bool isCurrentlyOn = encodeur.isOn() && jsonCom.getEtat() == 1;
    bool systemEnabled = (jsonCom.getEtat() == 1);

    if (!systemEnabled && wasOn) {
    encodeur.stall();  // force le "calage moteur"
    }

    if (isCurrentlyOn && !wasOn) {
        // ON vient de s'activer
        lcd.clear();
    }

    if (!isCurrentlyOn && wasOn) {
        // ON vient de se désactiver
        textToShowLine1 = "";
        textToShowLine2 = "";

        septSegUnits = 0;
        septSegTens = 0;
        septSegHundreds = 0;

        ledArray.show(0);
        lcd.clear();
    }

    // --------- MODE ON 
    if (isCurrentlyOn) {

        if(millis() >= lastLcdPrintTime + 100){
            lcd.clear();
            lcd.print(textToShowLine1);
            lcd.setCursor(0,1);
            lcd.print(textToShowLine2);
            lastLcdPrintTime = millis();
        }

        if(millis() >= lastSeptSegPrintTime + 10){
            septSeg.writeDigits(septSegUnits, septSegTens, septSegHundreds);
            lastSeptSegPrintTime = millis();
        }

        if(millis() >= lastInformationSendTime + 50){
            lastInformationSendTime = millis();

            accelerometre.lire_accelerometre();
            float angle = accelerometre.getAngle();
            jsonCom.sendSteering(millis(), angle/180);

            float accelPourcentage = pedaleAccel.lirePourcentage() / 100;
            float brakePourcentage = pedaleBrake.lirePourcentage() / 100;
            float gearShiftPourcentage = pedaleGearShift.lirePourcentage() / 100;
        }

        if(millis() >= lastInformationReadTime + 50){
            lastInformationReadTime = millis();

            if(jsonCom.readInformation()){
                int vitesse = jsonCom.getVitesse();
                septSegUnits = septSeg.getUnits(vitesse);
                septSegTens = septSeg.getTens(vitesse);
                septSegHundreds = septSeg.getHundreds(vitesse);

                int rpm = jsonCom.getRpm();
                int ledCount = rpm/800;
                ledArray.show(ledCount);
            }
        }
    }

    // Mise à jour du flag
    wasOn = isCurrentlyOn;
}