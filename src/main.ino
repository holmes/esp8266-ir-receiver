#include <Arduino.h>
#include "Bootstrap.cpp"

Bootstrap *bootstrap;

void setup() {
  Serial.begin(115200);

  IRrecv irrecv = IRrecv(14);
  IRMessageBroker messageBroker = IRMessageBroker();
  IRMessageReceiver messageRecevier = IRMessageReceiver(messageBroker, irrecv);

  Bootstrap bs = Bootstrap(messageBroker, messageRecevier);
  bs.setup();
  bootstrap = &bs;
}

void loop() {
  bootstrap->loop();
}
