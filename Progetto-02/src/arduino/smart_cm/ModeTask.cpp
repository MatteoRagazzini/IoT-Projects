#include "ModeTask.h"
#include "Arduino.h"
#include "MsgService.h"

ModeTask::ModeTask(){
    currentMode = 2; 
    nModes = 0;
}
void ModeTask::init(int period){
    Task::init(period);
    this->p = new MyPattern("M");
}

void ModeTask ::addMode(Mode* m){
    this->modes[nModes] = m;
    nModes++;
}

void ModeTask::tick(){
  int m = -1;
  if(MsgService.isMsgAvailable(*p)){
    m = MsgService.receiveMsg()->getContent().substring(1).toInt();
  }
  for(int i = 0; i < nModes; i++){
    if(this->modes[i]->isActive() || i == m){
      MsgService.sendMsg("M"+String(i));
      this->modes[currentMode]->switchOff();
      this->currentMode = i;
      this->modes[i]->switchOn();    
      }
  }
  
}
