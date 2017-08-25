#ifndef MQTTHandler_H
#define MQTTHandler_H

// Responsible for setting up MQTT and forwarding received
// messages to the broker.
class MQTTHandler {
public:
  void setup();
  void irCommandReceived();
};

struct MQTTConfig {

};

class MQTTHandlerFactory {
public:
  MQTTHandler build(MQTTConfig config);
};

#endif
