#include <Arduino.h>
#include <IRrecv.h>

#include "WifiInitializer.h"
#include "IRMessageReceiver.h"
#include "IRMessageBroker.h"
#include "MQTTHandler.h"

class Bootstrap {
public:
  explicit Bootstrap(const IRMessageBroker &messageBroker, const IRMessageReceiver &receiver,
    const WifiInitializer &wifiInitializer,  const MQTTHandlerFactory mqttFactory)
  : irMessageBroker(messageBroker), irMessageReceiver(receiver),
  wifiInitializer(wifiInitializer), mqttFactory(mqttFactory) {
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
    MQTTConfig config;
    MQTTHandler mqttHandler = mqttFactory.build(config);
    mqttHandler.setup();
  }

  void loop() {
    irMessageReceiver.loop();
  }

private:
  WifiInitializer wifiInitializer;
  IRMessageBroker irMessageBroker;
  IRMessageReceiver irMessageReceiver;
  MQTTHandlerFactory mqttFactory;
};
