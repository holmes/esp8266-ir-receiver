#ifndef IRMessageBroker_H
#define IRMessageBroker_H

#include <list>
#include <IRrecv.h>

class IRMessageBroker {
public:
  void setup();
  void registerHandler();
  void commandReceived();

private:
  std::list<int> l;
};

#endif
