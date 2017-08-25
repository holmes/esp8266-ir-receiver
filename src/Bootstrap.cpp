#include <Arduino.h>
#include "WifiInitializer.cpp"
#include "IRMessageReceiver.h"
#include "IRMessageBroker.h"
#include "MQTTHandler.cpp"

class Bootstrap {
public:
  explicit Bootstrap(const IRMessageBroker &messageBroker, const IRMessageReceiver &receiver)
  : irMessageBroker(messageBroker), irMessageReceiver(receiver) {
    // Initialized!
  }

  void setup() {
    Serial.println("\n\nBootstrap starting");

    irMessageBroker.setup();
    irMessageBroker.registerHandler();

    irMessageReceiver.setup();
    wifiInitializer.setup();

    using namespace std::placeholders; // for `_1`
    wifiInitializer.connect(std::bind(&Bootstrap::setupMQTT, this, _1));
  }

  void setupMQTT(bool wifiInitialized) {
    mqttHandler.setup();
  }

  void loop() {
    irMessageReceiver.loop();
  }

private:
  WifiInitializer wifiInitializer;
  IRMessageBroker irMessageBroker;
  IRMessageReceiver irMessageReceiver;
  MQTTHandler mqttHandler;
};
