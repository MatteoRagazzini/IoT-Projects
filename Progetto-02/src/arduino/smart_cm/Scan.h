#ifndef __SCAN__
#define __SCAN__

#include "Task.h"
#include "RadarImpl.h"
#include "Led.h"
#include "BlinkTask.h"

class Scan: public Task {

  int direction;
  BlinkTask* Ld;
  int delta;
  bool isOver;
  bool infinity;

public:

  Scan(int echoPin, int trigPin, int servoPin, BlinkTask* Ld){
    this->radar = new RadarImpl(echoPin, trigPin, servoPin);
    this->Ld = Ld;
  }
  
  void init(int period){
    Task::init(period);
    this->direction = 0;
    this->delta = 12;
    this->radar->on();
    this->isOver = false;
    this->radar->setPosition(this->direction);
  }
  
  void tick(){
    this->radar->scan();
    if(this->radar->detected()){
      this->Ld->setActive(true);
    }
    checkAlarm();
    this->direction += this->delta;
    this->isOver = this->direction > 180 || this->direction < 0;
    if(isOver){
      this->direction = 0;
      scanOver();
    }
    this->radar->setPosition(this->direction);
  }
  
  virtual void scanOver() = 0;
  
  virtual void checkAlarm() = 0;
  
  bool hasFinished(){
  return isOver;
  }

  void switchRadarOff(){
    this->radar->off();
  }
protected:
  RadarImpl* radar;
};


 

#endif
