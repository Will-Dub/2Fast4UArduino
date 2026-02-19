#include <Arduino.h>

#define CLK 2  // Canal A (CLK) connecté à la broche numérique ...
#define DT 3   // Canal B (DT) connecté à la broche numérique ...
#define SW 4   // Canal de bouton (SW) connecté à la broche numérique ...

int Dernier_statutCLK;  // Pour stocker le dernier état de CLK
int Statut_courantCLK;  // Pour stocker l'état actuel de CLK
int counter = 0;  // Suivre le nombre de rotations
bool BouttonAppuye = false;  // Suivre l'état du bouton


void Encodeur_init() {
  Dernier_statutCLK = digitalRead(CLK);
  pinMode(CLK, INPUT);
  pinMode(DT,INPUT);
  pinMode(SW, INPUT_PULLUP);
}


void Encodeur_update() {
  Statut_courantCLK = digitalRead(CLK);
  
  // Check for rotation
  if (Statut_courantCLK != Dernier_statutCLK) {
    if (digitalRead(DT) != Statut_courantCLK) {
      counter++; // Clockwise rotation
    } else {
      counter--; // Counter-clockwise rotation
    }
  }
  
  // Check for button press
  if (digitalRead(SW) == LOW) {
    BouttonAppuye = true; // Button is pressed
  } else if (digitalRead(SW) == HIGH) {
    BouttonAppuye = false; // Button is released
  }
  
  Dernier_statutCLK = Statut_courantCLK; // Update the last status of CLK
}







