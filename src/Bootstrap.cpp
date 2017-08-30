#include "Bootstrap.h"

Bootstrap::Bootstrap(const IRMessageBroker &messageBroker, const IRMessageReceiver &receiver,
  const WifiInitializer &wifiInitializer,  const MQTTHandlerFactory mqttFactory)
: irMessageBroker(messageBroker), irMessageReceiver(receiver),
wifiInitializer(wifiInitializer), mqttFactory(mqttFactory) {
  // Initialized!
}

void Bootstrap::setup() {
  Serial.println("\n\nBootstrap starting");

  using namespace std::placeholders;
  irMessageBroker.setup();
  irMessageBroker.registerHandler(std::bind(&Bootstrap::logDecodeResults, this, _1));

  irMessageReceiver.setup();

  wifiInitializer.setup();
  wifiInitializer.connect(std::bind(&Bootstrap::setupMQTT, this, _1));
}

void Bootstrap::setupMQTT(MQTTConfig mqttConfig) {
  MQTTConfig config;
  MQTTHandler mqttHandler = mqttFactory.build(config);
  mqttHandler.setup();

  using namespace std::placeholders;
  irMessageBroker.registerHandler(std::bind(&MQTTHandler::irCommandReceived, mqttHandler, _1));
}

void Bootstrap::loop() {
  irMessageReceiver.loop();
}

void Bootstrap::logDecodeResults(int i) {
  Serial.print("got something!");
}
