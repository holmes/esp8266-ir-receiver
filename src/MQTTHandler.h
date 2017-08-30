#ifndef MQTTHandler_H
#define MQTTHandler_H

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "WifiInitializer.h"

// Responsible for setting up MQTT and forwarding received
// messages to the broker.
class MQTTHandler {
public:
  explicit MQTTHandler(const PubSubClient &pubSubClient);
  void setup(MQTTConfig config);
  void loop();
  void irCommandReceived(int i);
private:
  PubSubClient client;
};

#endif
