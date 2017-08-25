#include <Arduino.h>
#include "IRMessageBroker.h"

#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

class IRMessageReceiver {
public:
  // explicit IRMessageReceiver(IRMessageBroker irMessageBroker, IRrecv irrecv);

  void setup() {
    Serial.println("Starting IR Message Decoder");
    // irrecv.enableIRIn();
  }

  void loop() {
    // if (irrecv.decode(&results)) {
    //   // print() & println() can't handle printing long longs. (uint64_t)
    //   serialPrintUint64(results.value, HEX);
    //   Serial.println("");
    //   irrecv.resume();  // Receive the next value
    // }
    delay(100);
  }

private:
  // IRMessageBroker irMessageBroker;
  // IRrecv irrecv;
};
