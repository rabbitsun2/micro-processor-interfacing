#include "pitches.h"

const int speakerpin = 8;


void setup() {
  // put your setup code here, to run once:

}

void loop() {
  tone(speakerpin, 500, 1000);
  delay(2000);

}
