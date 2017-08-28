#include <Arduino.h>
#include "MQTTHandler.h"

void MQTTHandler::setup() {
  Serial.println("Initializing MQTTHandler");
}

void MQTTHandler::irCommandReceived(int i) {
  // Pass it on!
}

MQTTHandler MQTTHandlerFactory::build(MQTTConfig config) {
  return MQTTHandler();
}
