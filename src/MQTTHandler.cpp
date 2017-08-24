#include <Arduino.h>

// Responsible for setting up MQTT and forwarding received
// messages to the broker.
class MQTTHandler {
public:
  void setup() {
    Serial.println("Initializing MQTTHandler");
  }

  void irCommandReceived() {
    // Pass it on!
  }
};
