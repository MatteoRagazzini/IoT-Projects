#ifndef __RADAR__
#define __RADAR__


class Radar {

public: 
  virtual void scan() = 0;
  virtual bool detected() = 0;
  virtual bool inAlarm() = 0;
  virtual bool inAlarmWithTracking() = 0;

};

#endif
