#include "BlinkTask.h"

BlinkTask::BlinkTask(int pin, bool isContinuous){
  this->pin = pin;    
  this->isContinuous = isContinuous;
}
  
void BlinkTask::init(int period){
  Task::init(period);
  led = new Led(pin); 
  state = OFF;    
}
  
void BlinkTask::tick(){
  switch (state){
    case OFF:
      led->switchOn();
      state = ON; 
      break;
    case ON:
      led->switchOff();
      state = OFF;
      if(!isContinuous){
        setActive(false);
      }
      break;
  }
}

void BlinkTask::switchOff(){
  led->switchOff();
  state=OFF;
}
