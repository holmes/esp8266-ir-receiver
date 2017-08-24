#include <Arduino.h>
#include "Bootstrap.cpp"

Bootstrap bootstrap;

void setup() {
  Serial.begin(115200);
  bootstrap.setup();
}

void loop() {
  // Nothing to loop!
}
