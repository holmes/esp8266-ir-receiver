#include <Arduino.h>
#include <functional>

#include "WifiInitializer.h"

// Needed for library.
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

void WifiInitializer::setup() {
  Serial.println("Initializing Wifi!");

  WiFiManager wifiManager;

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

  Serial.print("Connected with IP: ");
  Serial.print(WiFi.localIP());
}

void WifiInitializer::connect(WifiInitializedCallback wifiInitialized) {
  Serial.println("Wifi initialized, hitting callback");
  wifiInitialized(true);
}


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
