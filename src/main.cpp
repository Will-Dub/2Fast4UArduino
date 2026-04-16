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
#include "DetecteurMuons.h"
#include "Radio.h"

DetecteurMuons detecteurMuons(A3);
EncodeurRotatif encodeur(37,36,35); 
SeptSegments septSeg(9,8,7,5,4,14,3, 13,11,12); 
LedArray ledArray(31,30,29,28,49,48,47,46,45,44); 
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
Radio radio;
String textToShowLine1;
String textToShowLine2;

int septSegUnits;
int septSegTens;
int septSegHundreds;
float lastAccelAngle;

unsigned long lastLcdPrintTime;
unsigned long lastSeptSegPrintTime;
unsigned long lastInformationSendTime;
unsigned long lastStatusSendTime;
unsigned long lastInformationReadTime;
bool wasOn = false;

void setup() {
    Serial.begin(115200);

    js.begin();
    encodeur.begin(); 
    septSeg.begin(); 
    ledArray.begin(); 
    lcd.begin(16, 2);
    bouton1.buttonBegin(34);
    bouton2.buttonBegin(A14);
    bouton3.buttonBegin(32);
    detecteurMuons.begin();

    radio.radioSetup();
    radio.radioSetTime(14, 30, 0);
    radio.radioOff();

    lastLcdPrintTime = millis();
    lastSeptSegPrintTime = millis();
    lastInformationSendTime = millis();
    lastInformationReadTime = millis();
    lastStatusSendTime = millis();
    jsonCom.begin();

    ledArray.show(10);
}

void loop() {
    radio.radioUpdate();
    encodeur.update();

    if(millis() >= lastInformationReadTime + 50){
        lastInformationReadTime = millis();
        jsonCom.readInformation();
    }

    bool physicalKeyTurned = encodeur.isOn();
    bool pcResetFlag = jsonCom.getStartedResetFlag();

    if(pcResetFlag){
        encodeur.setOff();
        radio.radioOff();
    }

    // --------- TRANSITIONS ---------
    if (physicalKeyTurned && !wasOn) {
        // ON vient de démarrer
        lcd.clear();
        radio.radioOn();
    }

    if (!physicalKeyTurned && wasOn) {
        // ON vient de se désactiver
        textToShowLine1 = "";
        textToShowLine2 = "";

        septSegUnits = 0;
        septSegTens = 0;
        septSegHundreds = 0;

        ledArray.show(0);
        lcd.clear();
        septSeg.writeDigits(0, 0, 0);

        radio.radioOff();
    }

    // Envoie toujours le status
    if(millis() >= lastStatusSendTime + 200){
        lastStatusSendTime = millis();
        jsonCom.sendStatus(millis(), physicalKeyTurned);
    }

    // --------- MODE ON ---------
    if (physicalKeyTurned) {
        if(millis() >= lastLcdPrintTime + 100){
            lcd.clear();
            lcd.print(textToShowLine1);
            lcd.setCursor(0,1);
            lcd.print(textToShowLine2);
            lastLcdPrintTime = millis();
        }

        // Affiche le sept seg
        if(millis() >= lastSeptSegPrintTime + 10){
            int vitesse = jsonCom.getVitesse();
            septSegUnits = septSeg.getUnits(vitesse);
            septSegTens = septSeg.getTens(vitesse);
            septSegHundreds = septSeg.getHundreds(vitesse);

            septSeg.writeDigits(septSegUnits, septSegTens, septSegHundreds);
            lastSeptSegPrintTime = millis();
        }

        // Envoie les informations
        if(millis() >= lastInformationSendTime + 50){
            lastInformationSendTime = millis();
            accelerometre.lire_accelerometre();

            float angle = accelerometre.getAngle();
            jsonCom.sendSteering(millis(), angle / 180.0);

            // Envoie les valeurs des pédales
            float accelPourcentage = pedaleAccel.lirePourcentage() / 100.0;
            float brakePourcentage = pedaleBrake.lirePourcentage() / 100.0;
            float gearShiftPourcentage = pedaleGearShift.lirePourcentage() / 100.0;

            textToShowLine1 = "A: " + String(accelPourcentage) + ",B: " + String(brakePourcentage);
            textToShowLine2 = "Gear: " + String(gearShiftPourcentage);

            jsonCom.sendPedales(millis(), accelPourcentage, brakePourcentage, gearShiftPourcentage);

            // Envoie les données du joystick
            jsonCom.sendJoy(millis(), js.readX(), js.readY(), js.readButton());

            // Met à jour le lcd
            int rpm = jsonCom.getRpm();
            int ledCount = rpm / 800;
            ledArray.show(ledCount);
        }

        // Envoie la si un muons est detecté
        static bool muonDetecte = false;

        int muonValue = detecteurMuons.lireValeur();

        if (!muonDetecte && muonValue > 200) {
            muonDetecte = true;
            jsonCom.sendMuon(millis());
        }

        if(muonValue < 199){
            muonDetecte = false;
        }
    }

    // Mise à jour du flag
    wasOn = physicalKeyTurned;
}