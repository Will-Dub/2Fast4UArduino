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

    if (encodeur.isOn()) {   

    if(millis() >= lastLcdPrintTime + 100){
        lcd.clear();
        lcd.print(textToShowLine1);
        lcd.setCursor(0,1);
        lcd.print(textToShowLine2);
        lastLcdPrintTime = millis();
    }

    if(millis() >= lastSeptSegPrintTime + 10){
        septSeg.writeDigits(septSegUnits, septSegTens, septSegHundreds); //
        lastSeptSegPrintTime = millis();
    }

    // TODO tous mettre dans un packet
    // Envoie les valeurs de l'accel
    if(millis() >= lastInformationSendTime + 50){
        lastInformationSendTime = millis();
        accelerometre.lire_accelerometre();

        float angle = accelerometre.getAngle();
        jsonCom.sendSteering(millis(), angle/180);

        // Envoie les valeurs des pédales
        float accelPourcentage = pedaleAccel.lirePourcentage() / 100;
        float brakePourcentage = pedaleBrake.lirePourcentage() / 100;
        float gearShiftPourcentage = pedaleGearShift.lirePourcentage() / 100;

        textToShowLine1 = "A: ";
        textToShowLine1 += accelPourcentage;
        textToShowLine1 += ",B: ";
        textToShowLine1 += brakePourcentage;
        textToShowLine2 = "Gear: ";
        textToShowLine2 += gearShiftPourcentage;

        jsonCom.sendPedales(millis(), accelPourcentage, brakePourcentage, gearShiftPourcentage);

        // Envoie les données du joystick
        jsonCom.sendJoy(millis(), js.readX(), js.readY(), js.readButton());
    }

    // Met à jour les données sur le ledArray et 7-seg
    if(millis() >= lastInformationReadTime + 50){
        lastInformationReadTime = millis();
        if(jsonCom.readInformation()){
            int vitesse = jsonCom.getVitesse();
            septSegUnits = septSeg.getUnits(vitesse);
            septSegTens = septSeg.getTens(vitesse);
            septSegHundreds = septSeg.getHundreds(vitesse);

            int rpm = jsonCom.getRpm();
            // TODO: Meilleur calcul
            int ledCount = rpm/800;
            ledArray.show(ledCount);
        }
    }

}
    else {
        // État OFF
        textToShowLine1 = "";
        textToShowLine2 = "";

        septSegUnits = 0;
        septSegTens = 0;
        septSegHundreds = 0;

        ledArray.show(0);
        lcd.clear();
        lcd.print("");
    }

}
