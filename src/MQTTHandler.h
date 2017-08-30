#ifndef MQTTHandler_H
#define MQTTHandler_H

#include "WifiInitializer.h"

// Responsible for setting up MQTT and forwarding received
// messages to the broker.
class MQTTHandler {
public:
  void setup();
  void irCommandReceived(int i);
};

class MQTTHandlerFactory {
public:
  MQTTHandler build(MQTTConfig config);
};

#endif
