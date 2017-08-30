#include <Arduino.h>
#include "MQTTHandler.h"

void MQTTHandler::setup() {
  Serial.println("Initializing MQTTHandler");
}

void MQTTHandler::irCommandReceived(int i) {
  // Pass it on!
}

MQTTHandler MQTTHandlerFactory::build(MQTTConfig config) {
  Serial.print("MQTT Configured: ");
  Serial.println(config.mqtt_server);
  return MQTTHandler();
}
