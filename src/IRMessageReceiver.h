#ifndef IRMessageReceiver_H
#define IRMessageReceiver_H

#include "IRMessageBroker.h"
#include <IRrecv.h>

class IRMessageReceiver {
public:
  explicit IRMessageReceiver(const IRMessageBroker &irMessageBroker, const IRrecv &irrecv);

  void setup();
  void loop();

private:
  const IRMessageBroker irMessageBroker;
  IRrecv irrecv;
};

#endif
