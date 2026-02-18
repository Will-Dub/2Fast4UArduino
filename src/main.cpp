#include <Arduino.h>
#include "SeptSegments.h"

void setup() {
    segmentsSetup();
}

void loop() {
    writeSpeed(UNITS, TENS, HUNDREDS);
}