#ifndef IRMessageReceiver_H
#define IRMessageReceiver_H

#include <IRrecv.h>

class IRMessageReceiver {
public:
  explicit IRMessageReceiver(const IRrecv &irrecv);

  void setup();
  void loop();

private:
  IRrecv irrecv;
};

#endif
