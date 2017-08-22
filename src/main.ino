#include <Arduino.h>

void setup() {
    Serial.begin(115200);
  }

  void loop() {
    Serial.println("oh shit, it works");    
    delay(1000);
  }
