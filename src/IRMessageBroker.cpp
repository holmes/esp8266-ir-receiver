#include <Arduino.h>

class IRMessageBroker {
public:
  void setup() {
    Serial.println("Intiailzing IRMessageBroker");
  }

  void registerHandler() {
    Serial.println("Added listener");
  }

  void commandReceived() {
    Serial.println("Dispatching command to listeners");
  }
};
