#ifndef WifiInitializer_H
#define WifiInitializer_H

#include <functional>

// Callback function when a IR message is received.
typedef std::function<void(bool)> WifiInitializedCallback;

class WifiInitializer {
public:
  void setup();
  void connect(WifiInitializedCallback wifiInitialized);
};

#endif
