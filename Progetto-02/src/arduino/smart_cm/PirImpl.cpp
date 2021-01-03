#include "PirImpl.h"
#include "Arduino.h"
#include "MsgService.h"

PirImpl::PirImpl(int pin){
    this->pin = pin;
    pinMode(pin, INPUT);
}

void PirImpl::calibrate(){
  for(int i = 0; i < calibrationTimeSec; i++){
      delay(1000);
  }
  MsgService.sendMsg("C");
}

int PirImpl::hasDetected(){
    return digitalRead(pin) == HIGH;
}
