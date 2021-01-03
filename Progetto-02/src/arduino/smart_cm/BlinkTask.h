#ifndef __BLINKTASK__
#define __BLINKTASK__

#include "Task.h"
#include "Led.h"

class BlinkTask: public Task {

  int pin;
  Light* led;
  bool isContinuous;
  enum { ON, OFF} state;

public:

  BlinkTask(int pin, bool isContinuous);  
  void init(int period);  
  void tick();
  void switchOff();
};

#endif
