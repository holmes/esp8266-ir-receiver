#include <Arduino.h>

#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "WifiInitializer.h"

IRrecv irrecv = IRrecv(14);
WiFiClient espClient;

PubSubClient mqttClient(espClient);

void setupMQTT(MQTTConfig mqttConfig) {
  mqttClient.setServer("192.168.1.5", 1883);

  if (!mqttClient.connect("IRRECVR-PUTINAREALID", "openhab", "mqtt@165")) {
    Serial.println("Connecting failed!");
  }

  Serial.printf("MQTT Configured: %s\n", mqttConfig.mqtt_server);
}

// Print a uint64_t/unsigned long long to the Serial port
// Serial.print() can't handle printing long longs. (uint64_t)
//
// Args:
//   input: The value to print
//   base: The output base.
// Note: Based on Arduino's Print::printNumber()
void sendCode(uint64_t input, uint8_t base = 16) {
  char buf[8 * sizeof(input) + 1];  // Assumes 8-bit chars plus zero byte.
  char *str = &buf[sizeof(buf) - 1];

  *str = '\0';

  // prevent crash if called with base == 1
  if (base < 2) base = 10;

  do {
    char c = input % base;
    input /= base;

    *--str = c < 10 ? c + '0' : c + 'A' - 10;
  } while (input);

  Serial.printf("Received IR Code: %s\n", str);
  mqttClient.publish("ir/family", str);
}

void setup() {
  Serial.begin(115200);

  Serial.println("Starting IR Message Decoding");
  irrecv.enableIRIn();

  Serial.println("Initializing Wifi");
  WifiInitializer wifiInitializer = WifiInitializer();
  wifiInitializer.setup();
  wifiInitializer.connect(setupMQTT);
}

void loop() {
  decode_results results;
  if (irrecv.decode(&results)) {
    sendCode(results.value);
    irrecv.resume();
  }

  delay(100);
  mqttClient.loop();
}
