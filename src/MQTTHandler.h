#ifndef MQTTHandler_H
#define MQTTHandler_H

// Responsible for setting up MQTT and forwarding received
// messages to the broker.
class MQTTHandler {
public:
  void setup();
  void irCommandReceived();
};

#endif
