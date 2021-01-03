#ifndef __RADARIMPL__
#define __RADARIMPL__

#include "Radar.h"
#include "SonarImpl.h"
#include "Servo_motor_impl.h"
#include "Arduino.h"


class RadarImpl: public Radar, public ServoMotorImpl, public SonarImpl {
  float currentDistance;

public: 
  RadarImpl(int echoSonarPin, int trigSonarPin, int servoPin);
  void scan();
  bool detected();
  bool inAlarm();
  bool inAlarmWithTracking();

};

#endif
