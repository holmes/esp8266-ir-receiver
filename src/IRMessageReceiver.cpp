#include <Arduino.h>

#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

#include "IRMessageReceiver.h"

IRMessageReceiver::IRMessageReceiver(const IRrecv &receiver)
: irrecv(receiver) {
  // We're initialized!
}

void IRMessageReceiver::setup() {
  Serial.println("Starting IR Message Decoder");
  irrecv.enableIRIn();
}

void IRMessageReceiver::loop() {
  decode_results results;

  if (irrecv.decode(&results)) {
    // print() & println() can't handle printing long longs. (uint64_t)
    serialPrintUint64(results.value, HEX);
    Serial.println("");
    irrecv.resume();  // Receive the next value
  }

  delay(100);
}
