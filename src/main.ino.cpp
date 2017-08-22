# 1 "/var/folders/_7/zdkhxrgx3t3_x1yb7bbhw1bm0000gn/T/tmp_MtRo6"
#include <Arduino.h>
# 1 "/work/nodemcu-ir-receiver/src/main.ino"
#include <Arduino.h>
void setup();
#line 3 "/work/nodemcu-ir-receiver/src/main.ino"
void setup() {
    Serial.begin(115200);
  }

  void loop() {
    Serial.println("oh shit, it works");
    delay(1000);
  }