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
EncodeurRotatif encodeur(37,36,35); //
SeptSegments septSeg(9,8,7,5,4,2,3, 10,11,12); //
LedArray ledArray(53,52,51,50,49,48,47,46,45,44); //
Pedale pedale (A3);

Joystick js(A0, A1, 2);
LiquidCrystal lcd(43,42,41,40,39,38);
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
unsigned long lastAccelRotationTime;

void setup() {
    js.begin();
    encodeur.begin(); //
    septSeg.begin(); //
    ledArray.begin(); //
    lcd.begin(16, 2);
    bouton1.buttonBegin(34);
    bouton2.buttonBegin(A14);
    bouton3.buttonBegin(32);

    lastLcdPrintTime = millis();
    lastSeptSegPrintTime = millis();
    lastAccelRotationTime = millis();

    jsonCom.begin();

    ledArray.show(10);
}

void loop() {
//  writeSpeed(0,2,4);
//  writeSpeed(UNITS, TENS, HUNDREDS);
    encodeur.update();
   // Serial.print(numChar);

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

    switch (encodeur.getCounter()) //
    {
        case 0: //État des boutons
        {
            textToShowLine1 = bouton1.buttonRead() ? "Gas:1 " : "Gas:0 ";
            textToShowLine1 += bouton2.buttonReadBreak() ? "Break:1 " : "Break:0 ";
            textToShowLine2 = bouton3.buttonRead() ? "Clutch:1 " : "Clutch:0 ";
            break;
        }
        case 2: //Module accéléromètre
        {
            lire_accelerometre();
            textToShowLine1 = "X: ";
            textToShowLine1 += getXScaled();
            textToShowLine1 += " Y: ";
            textToShowLine1 += getYScaled();
            textToShowLine2 = "angle: ";
            textToShowLine2 += getAngle();
            break;
        }
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
        case 6:
        {
            textToShowLine1 = pedale.lirePourcentage();
            break;
        }
        default:
        {
            textToShowLine1 = encodeur.getCounter();
            textToShowLine1 += " n'est pas valide";
            textToShowLine2 = "";
            break;
        }
    }

    // Met à jour la valeur du potentiomètre
    float pourcentage = pedale.lirePourcentage();
    septSegUnits = septSeg.getUnits(pourcentage);
    septSegTens = septSeg.getTens(pourcentage);
    septSegHundreds = septSeg.getHundreds(pourcentage); 
}