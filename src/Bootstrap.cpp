#include "Bootstrap.h"

Bootstrap::Bootstrap(const IRMessageReceiver &receiver,
  const WifiInitializer &wifiInitializer,
  const MQTTHandler mqttHandler)
:irMessageReceiver(receiver), wifiInitializer(wifiInitializer), mqttHandler(mqttHandler) {
  // Initialized!
}

void Bootstrap::setup() {
  irMessageReceiver.setup();
  wifiInitializer.setup();

  using namespace std::placeholders;
  wifiInitializer.connect(std::bind(&Bootstrap::setupMQTT, this, _1));
}

void Bootstrap::setupMQTT(MQTTConfig mqttConfig) {
  mqttHandler.setup(mqttConfig);

  using namespace std::placeholders;
  // irMessageBroker.registerHandler(std::bind(&MQTTHandler::irCommandReceived, mqttHandler, _1));
}

void Bootstrap::loop() {
  irMessageReceiver.loop();
  mqttHandler.loop();
}
