#ifndef WifiInitializer_H
#define WifiInitializer_H

#include <functional>

// The parameters that were configured during Wifi Initialization.
struct MQTTConfig {
  char mqtt_server[40] = "";
  char mqtt_port[5] = "";
  char mqtt_user[20] = "";
  char mqtt_pass[20] = "";
  char mqtt_topic[40] = "";
};

// Callback function when a IR message is received.
typedef std::function<void(MQTTConfig mqttConfig)> WifiInitializedCallback;

class WifiInitializer {
public:
  void setup();
  void connect(WifiInitializedCallback wifiInitialized);
  MQTTConfig config;

private:
  bool shouldResetSettings;
};

#endif
