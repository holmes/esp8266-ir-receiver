#include "Bootstrap.h"

Bootstrap::Bootstrap(const IRMessageBroker &messageBroker, const IRMessageReceiver &receiver,
  const WifiInitializer &wifiInitializer,  const MQTTHandlerFactory mqttFactory)
: irMessageBroker(messageBroker), irMessageReceiver(receiver),
wifiInitializer(wifiInitializer), mqttFactory(mqttFactory) {
  // Initialized!
}

void Bootstrap::setup() {
  Serial.println("\n\nBootstrap starting");

  irMessageBroker.setup();
  // irMessageBroker.registerHandler(
  //   [&this](int i) { return this->logDecodeResults(i); });

  // caller.connectCallback(
  // [&callee](int i) { return callee.callbackFunction(i); });

  irMessageReceiver.setup();
  wifiInitializer.setup();

  using namespace std::placeholders; // for `_1`
  wifiInitializer.connect(std::bind(&Bootstrap::setupMQTT, this, _1));
}

void Bootstrap::setupMQTT(bool wifiInitialized) {
  MQTTConfig config;
  MQTTHandler mqttHandler = mqttFactory.build(config);
  mqttHandler.setup();

  irMessageBroker.registerHandler(
    [&mqttHandler](int i) { return mqttHandler.irCommandReceived(i); });
}

void Bootstrap::loop() {
  irMessageReceiver.loop();
}

int Bootstrap::logDecodeResults(int i) {
  Serial.print("got something!");
}
