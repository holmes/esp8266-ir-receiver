#include <Arduino.h>
#include <functional>

class WifiInitializer {

public:
  void setup() {
    Serial.println("Initializing Wifi!");
  }

  void connect(std::function<void(bool)> wifiInitialized) {
    Serial.println("Wifi initialized, hitting callback");
    wifiInitialized(true);
  }
};


// class EventHandler
// {
// public:
//   void addHandler(std::function<void(int)> callback)
//   {
//     Serial.println("Handler added...");
//     callback(1);
//   }
// };
//
// class MyClass
// {
// public:
//   MyClass();
//   void wifiInitialized(int x) {
//     Serial.println("things are fun!");
//   }
// private:
//   EventHandler* handler;
//   int private_x;
// };
//
// MyClass::MyClass()
// {
//   using namespace std::placeholders; // for `_1`
//
//   private_x = 5;
//   handler->addHandler(std::bind(&MyClass::wifiInitialized, this, _1));
//
//   this->wifiInitialized(223);
// }

// void MyClass::wifiInitialized(int x)
// {
//   // No longer needs an explicit `instance` argument,
//   // as `this` is set up properly
//   Serial.println("things are fun!");
// }
