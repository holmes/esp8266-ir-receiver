#ifndef WifiInitializer_H
#define WifiInitializer_H

#include <functional>

class WifiInitializer {
public:
  void setup();
  void connect(std::function<void(bool)> wifiInitialized);
};

#endif
