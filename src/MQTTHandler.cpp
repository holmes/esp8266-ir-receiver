#include <Arduino.h>
#include "MQTTHandler.h"

MQTTHandler::MQTTHandler(const PubSubClient &pubSubClient) : client(pubSubClient) {
  // We're initialized!
}

void MQTTHandler::setup(MQTTConfig config) {
  Serial.printf("MQTT Configured: %s\n", config.mqtt_server);

  client.setServer("192.168.1.5", 1883);

  if (!client.connect("IRRECVR-PUTINAREALID", "openhab", "mqtt@165")) {
    Serial.println("Connecting failed!");
  }

  if (!client.publish("test/topic", "diditwork")) {
    Serial.println("Publishing Failed!");
  }
}

void MQTTHandler::loop() {
  client.loop();
}

void MQTTHandler::irCommandReceived(int i) {
  // Pass it on!
}
