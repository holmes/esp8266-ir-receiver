#ifndef IRMessageBroker_H
#define IRMessageBroker_H

#include <functional>
#include <list>
#include <IRrecv.h>

// Callback function when a IR message is received.
typedef std::function<void(int)> IRMessageReceivedCallback;

class IRMessageBroker {
public:
  void setup();
  void registerHandler(IRMessageReceivedCallback handler);
  void commandReceived();

private:
  std::list<int> l;
};

#endif
