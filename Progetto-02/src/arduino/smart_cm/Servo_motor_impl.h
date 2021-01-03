#ifndef __SERVO_MOTOR_IMPL__
#define __SERVO_MOTOR_IMPL__

#include "Servo_motor.h"
#include "Arduino.h"
#include "ServoTimer2.h"

class ServoMotorImpl: public ServoMotor {

public:
  ServoMotorImpl(int pin);

  void on();
  void setPosition(int newAngle);
  int getPosition();
  void off();
    
private:
  int pin; 
  int angle;
  ServoTimer2 motor; 
  // 750 -> 0, 2250 -> 180 
  // 750 + angle*(2250-750)/180
  const float coeff = (2250.0-750.0)/180;
};

#endif
