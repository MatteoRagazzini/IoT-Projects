#include "ReadPotTask.h"
#include "Arduino.h"

ReadPotTask::ReadPotTask(int pin, Scan* s){
  this->pot = new PotImpl(pin); 
  this->s = s;
  this->p = new MyPattern("P");
  this->lastMecanicPotValue = 1;
  this->lastSerialPotValue = 1;
}
  
void ReadPotTask::init(int period){
  Task::init(period);
}
  
void ReadPotTask::tick(){
  if(this->s->hasFinished()){
    int v = this->pot->getValue();
    int m = map(v, 0, 1023, 1, 5);
    if(MsgService.isMsgAvailable(*p)){
      lastMecanicPotValue = m;
      m = MsgService.receiveMsg()->getContent().substring(1).toInt();
      lastSerialPotValue = m;
    }else{
      if(lastMecanicPotValue==m){
        m=lastSerialPotValue;
      }else{
        lastMecanicPotValue = m;
      }
    }
    this->s->init(m*125); 
  }
}
