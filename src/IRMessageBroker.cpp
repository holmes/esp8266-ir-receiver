#include <Arduino.h>
#include <list>

#include "IRMessageBroker.h"

void IRMessageBroker::setup() {
  Serial.println("Intiailzing IRMessageBroker");
}

void IRMessageBroker::registerHandler() {
  Serial.println("Added listener");
  l.push_back(1);
  Serial.printf("new size is %d\n", l.size());
  l.push_back(1);
  Serial.printf("new size is %d\n", l.size());
}

void IRMessageBroker::commandReceived() {
  Serial.println("Dispatching command to listeners");
}
