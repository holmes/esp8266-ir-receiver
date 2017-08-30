#include <Arduino.h>
#include "MQTTHandler.h"

MQTTHandler::MQTTHandler(const PubSubClient &pubSubClient) : client(pubSubClient) {
  // We're initialized!
}

void callback(char* topic, byte* payload, unsigned int length) {
 Serial.print("Message arrived [");
 Serial.print(topic);
 Serial.print("] ");
}

void MQTTHandler::setup(MQTTConfig config) {
  Serial.printf("MQTT Configured: %s\n", config.mqtt_server);

  client.setServer("192.168.1.5", 1883)
        .setCallback(callback);

  if (!client.connect("IRRECVR-PUTINAREALID", "openhab", "mqtt@165")) {
    Serial.println("Connecting failed!");
  }

  if (!client.subscribe("test/topic")) {
    Serial.println("Subscribing Failed!");
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
