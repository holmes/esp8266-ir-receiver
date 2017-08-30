#include <FS.h>
#include <Arduino.h>
#include <functional>

#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <ArduinoJson.h>

#include "WifiInitializer.h"

// Having a hard time mastering the art of C++ callbacks.
bool shouldSaveConfig = false;
void saveConfigCallback() {
  shouldSaveConfig = true;
}

void WifiInitializer::setup() {
  Serial.println("Initializing Wifi!");

  if (SPIFFS.begin()) {
    Serial.println("Mounted File System");

    if (SPIFFS.exists("/mqttConfig.json")) {
      Serial.println("Found the mqttConfig file");
      File configFile = SPIFFS.open("/mqttConfig.json", "r");
      if (configFile) {
        Serial.println("Opened mqttConfig.json");
        size_t size = configFile.size();
        // Allocate a buffer to store contents of the file.
        std::unique_ptr<char[]> buf(new char[size]);
        configFile.readBytes(buf.get(), size);
        configFile.close();

        DynamicJsonBuffer jsonBuffer;
        JsonObject& json = jsonBuffer.parseObject(buf.get());
        json.printTo(Serial);

        if (json.success()) {
          Serial.println("\nParsed mqttConfig.json");
          strcpy(config.mqtt_server, json["mqtt_server"]);
          strcpy(config.mqtt_port, json["mqtt_port"]);
          strcpy(config.mqtt_user, json["mqtt_user"]);
          strcpy(config.mqtt_pass, json["mqtt_pass"]);
          strcpy(config.mqtt_topic, json["mqtt_topic"]);
        } else {
          Serial.println("\nFailed to load mqttConfig.json");
          shouldResetSettings = true;
        }
      } else {
        Serial.println("Unable to open mqttConfig.json");
        shouldResetSettings = true;
      }
    } else {
      Serial.println("Didn't find mqttConfig.json");
      shouldResetSettings = true;
    }
  } else {
    // Don't bother resetting the settings. If we can't load it now
    // we won't be able to save it later.
    Serial.println("Failed to mount the file system. That's very bad.");
  }
}

void WifiInitializer::connect(WifiInitializedCallback wifiInitialized) {
  // Only need this locally. Don't shoot me for not DI-ing it.
  using namespace std::placeholders;
  WiFiManager wifiManager;
  wifiManager.setSaveConfigCallback(saveConfigCallback);

  if (shouldResetSettings) {
    wifiManager.resetSettings();
  }

  WiFiManagerParameter custom_mqtt_server("server", "MQTT Server", config.mqtt_server, 40);
  WiFiManagerParameter custom_mqtt_port("port", "MQTT Port", config.mqtt_port, 5);
  WiFiManagerParameter custom_mqtt_user("user", "MQTT Username", config.mqtt_user, 32);
  WiFiManagerParameter custom_mqtt_pass("pass", "MQTT Password", config.mqtt_pass, 32);
  WiFiManagerParameter custom_mqtt_topic("topic", "MQTT Topic", config.mqtt_topic, 80);

  wifiManager.addParameter(&custom_mqtt_server);
  wifiManager.addParameter(&custom_mqtt_port);
  wifiManager.addParameter(&custom_mqtt_user);
  wifiManager.addParameter(&custom_mqtt_pass);
  wifiManager.addParameter(&custom_mqtt_topic);

  char mySSID[17];
  char myPASS[7];
  sprintf(mySSID,"IRRECVR-00%06X", ESP.getChipId());
  sprintf(myPASS,"00%06X", ESP.getChipId());
  if (!wifiManager.autoConnect(mySSID, myPASS)) {
    Serial.println("*IR: failed to connect and hit timeout");
    delay(3000);
    ESP.reset();
    delay(5000);
  }

  // WiFi Connected, let's copy over the params.
  strcpy(config.mqtt_server, custom_mqtt_server.getValue());
  strcpy(config.mqtt_port, custom_mqtt_port.getValue());
  strcpy(config.mqtt_user, custom_mqtt_user.getValue());
  strcpy(config.mqtt_pass, custom_mqtt_pass.getValue());
  strcpy(config.mqtt_topic, custom_mqtt_topic.getValue());

  // Save the custom parameters to FS.
  if (shouldSaveConfig) {
    Serial.println("Saving MQTTConfig to mqttConfig.json");
    DynamicJsonBuffer jsonBuffer;
    JsonObject& json = jsonBuffer.createObject();
    json["mqtt_server"] = config.mqtt_server;
    json["mqtt_port"] = config.mqtt_port;
    json["mqtt_user"] = config.mqtt_user;
    json["mqtt_pass"] = config.mqtt_pass;
    json["mqtt_topic"] = config.mqtt_topic;

    File configFile = SPIFFS.open("/mqttConfig.json", "w");
    if (!configFile) {
      Serial.println("Failed to open config file for writing");
    }

    json.printTo(Serial);
    json.printTo(configFile);
    configFile.close();
  }

  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  wifiInitialized(config);
}
