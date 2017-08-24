#include <Arduino.h>
#include "IRMessageBroker.cpp"

class IRMessageReceiver {
public:
  void setup() {
    Serial.println("Starting IR Message Decoder");

    // Set a callback for #handleMessage.
  }

  void handleMessage() {
    irMessageBroker.commandReceived();
  }

private:
  IRMessageBroker irMessageBroker;
};
