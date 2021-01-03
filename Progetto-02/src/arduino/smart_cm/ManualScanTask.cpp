#include "ManualScanTask.h"
#include "Arduino.h"
#include "MsgService.h"

ManualScanTask::ManualScanTask(int echoPin, int trigPin, int servoPin, BlinkTask* LD){
  this->radar = new RadarImpl(echoPin, trigPin, servoPin);
  this->LD = LD;
  this->p = new MyPattern("S");
}
  
void ManualScanTask::init(int period){
  Task::init(period);
  this->radar->on();
  this->radar->setPosition(0);
}

void ManualScanTask::tick(){
 if (MsgService.isMsgAvailable(*p)){
   Msg* msg = MsgService.receiveMsg();
   int angle = msg->getContent().substring(1).toInt(); 
   this->radar->setPosition(angle);
   this->radar->scan();
   if(this->radar->detected()){
     this->LD->setActive(true);
   }
   delete msg;
 }
}

void ManualScanTask::radarSwitchOff(){
  this->radar->off();
}
