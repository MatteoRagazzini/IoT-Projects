#ifndef __PIRDETECTION__
#define __PIRDETECTION__

#include "Task.h"
#include "PirImpl.h"
#include "Scan.h"

class PirDetectionTask: public Task {

PirImpl* pir;
Task* s;
long last;

public:

  PirDetectionTask(int pin, Task*s);  
  void init(int period);  
  void tick();
};

#endif
