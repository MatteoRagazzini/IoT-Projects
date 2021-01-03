#ifndef __TRACKINGTASK__
#define __TRACKINGTASK__

#include "Task.h"
#include "Scan.h"

class TrackingTask: public Task {

  Scan* s;
  RadarImpl* r;
  
public:

  TrackingTask();  
  void init(int period);  
  void tick();
  void attachScan(Scan* s);
  void setRadar(RadarImpl* r);
};

#endif
