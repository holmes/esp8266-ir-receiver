#include <Arduino.h>

#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

#include "IRMessageBroker.h"
#include "IRMessageReceiver.h"

IRMessageReceiver::IRMessageReceiver(const IRMessageBroker &broker, const IRrecv &receiver)
: irMessageBroker(broker), irrecv(receiver) {
  // We're initialized!
}

void IRMessageReceiver::setup() {
  Serial.println("Starting IR Message Decoder");
  irrecv.enableIRIn();
}

void IRMessageReceiver::loop() {
  if (irrecv.decode(&results)) {
    // print() & println() can't handle printing long longs. (uint64_t)
    serialPrintUint64(results.value, HEX);
    Serial.println("");
    irrecv.resume();  // Receive the next value
  }

  delay(100);
}
