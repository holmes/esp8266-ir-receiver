#include <Arduino.h>
#include "WifiInitializer.cpp"
#include "IRMessageReceiver.cpp"
#include "MQTTHandler.cpp"

class Bootstrap {
public:
  void setup() {
    Serial.println("\n\nBootstrap starting");

    irMessageReceiver.setup();
    wifiInitializer.setup();

    using namespace std::placeholders; // for `_1`
    wifiInitializer.connect(std::bind(&Bootstrap::setupMQTT, this, _1));
  }

  void setupMQTT(bool wifiInitialized) {
    mqttHandler.setup();

    // Pas mqttHandler to irMessageBroker.
    irMessageBroker.registerHandler();
  }

private:
  WifiInitializer wifiInitializer;
  IRMessageBroker irMessageBroker;
  IRMessageReceiver irMessageReceiver;
  MQTTHandler mqttHandler;
};
