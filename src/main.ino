#include <Arduino.h>
#include "Bootstrap.cpp"

Bootstrap *bootstrap;

void setup() {
  Serial.begin(115200);

  IRrecv irrecv = IRrecv(14);
  IRMessageBroker messageBroker = IRMessageBroker();
  IRMessageReceiver messageRecevier = IRMessageReceiver(messageBroker, irrecv);

  WifiInitializer wifiInitializer = WifiInitializer();
  MQTTHandlerFactory mqttFactory = MQTTHandlerFactory();

  Bootstrap bs = Bootstrap(messageBroker, messageRecevier, wifiInitializer, mqttFactory);
  bs.setup();
  bootstrap = &bs;
}

void loop() {
  bootstrap->loop();
}
