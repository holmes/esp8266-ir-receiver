#ifndef Bootstrap_H
#define Bootstrap_H

#include <Arduino.h>

#include "WifiInitializer.h"
#include "IRMessageReceiver.h"
#include "MQTTHandler.h"

class Bootstrap {
public:
  explicit Bootstrap(const IRMessageReceiver &receiver,
    const WifiInitializer &wifiInitializer,
    const MQTTHandler mqttHandler);

  void setup();
  void setupMQTT(MQTTConfig mqttConfig);
  void loop();
  void logDecodeResults(int i);

private:
  WifiInitializer wifiInitializer;
  IRMessageReceiver irMessageReceiver;
  MQTTHandler mqttHandler;
};

#endif
