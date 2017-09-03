#include <Arduino.h>
#include "Bootstrap.h"

WiFiClient espClient;
Bootstrap *bootstrap;

void setup() {
  Serial.begin(115200);

  IRrecv irrecv = IRrecv(14);
  IRMessageBroker messageBroker = IRMessageBroker();
  IRMessageReceiver messageRecevier = IRMessageReceiver(messageBroker, irrecv);

  WifiInitializer wifiInitializer = WifiInitializer();

  PubSubClient client(espClient);
  MQTTHandler mqttHandler = MQTTHandler(client);

  Bootstrap bs = Bootstrap(messageBroker, messageRecevier, wifiInitializer, mqttHandler);
  bootstrap = &bs;

  bootstrap->setup();
}

void loop() {
  bootstrap->loop();
}
