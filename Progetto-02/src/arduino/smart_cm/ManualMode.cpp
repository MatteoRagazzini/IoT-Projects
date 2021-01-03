#include "ManualMode.h"
#include "Arduino.h"

ManualMode::ManualMode(int pin, ManualScanTask* s){
    Mode::attachButton(pin);
    this->s = s;
}

void ManualMode::switchOn(){
    this->s->setActive(true);
    this->s->init(125);
}

void ManualMode::switchOff(){
    this->s->setActive(false);
    this->s->radarSwitchOff();
}
