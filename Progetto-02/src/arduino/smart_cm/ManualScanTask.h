#ifndef __MANUALTASK__
#define __MANUALTASK__

#include "Task.h"
#include "RadarImpl.h"
#include "BlinkTask.h"
#include "MyPattern.h"

class ManualScanTask: public Task {

RadarImpl* radar;
BlinkTask* LD;
Pattern* p;


public:

  ManualScanTask(int echoPin, int trigPin, int servoPin, BlinkTask* LD);  
  void init(int period);  
  void tick();
  void radarSwitchOff();
};

#endif
