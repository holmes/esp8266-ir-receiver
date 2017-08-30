#ifndef Bootstrap_H
#define Bootstrap_H

#include <Arduino.h>

#include "WifiInitializer.h"
#include "IRMessageReceiver.h"
#include "IRMessageBroker.h"
#include "MQTTHandler.h"

class Bootstrap {
public:
  explicit Bootstrap(const IRMessageBroker &messageBroker, const IRMessageReceiver &receiver,
    const WifiInitializer &wifiInitializer,  const MQTTHandler mqttHandler);

  void setup();
  void setupMQTT(MQTTConfig mqttConfig);
  void loop();
  void logDecodeResults(int i);

private:
  WifiInitializer wifiInitializer;
  IRMessageBroker irMessageBroker;
  IRMessageReceiver irMessageReceiver;
  MQTTHandler mqttHandler;
};

#endif
