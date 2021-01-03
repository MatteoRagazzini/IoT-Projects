#include "RadarImpl.h"
#include "MsgService.h"

RadarImpl::RadarImpl(int echoSonarPin, int trigSonarPin, int servoPin):ServoMotorImpl(servoPin),SonarImpl(echoSonarPin,trigSonarPin){
  this->currentDistance = 0;
} 

void RadarImpl::scan(){
    this->currentDistance = getDistance();
    if(detected()){
      MsgService.sendMsg("R:" + String(getPosition()) + ":"+String(this->currentDistance));
    }else{
      MsgService.sendMsg("R:0:0");
    }
}

bool RadarImpl::detected(){
  return this->currentDistance < 0.60;
}

bool RadarImpl::inAlarm(){
  return this->currentDistance < 0.40 && this->currentDistance > 0.20;
}
bool RadarImpl::inAlarmWithTracking(){
  return this->currentDistance <= 0.20;
}
