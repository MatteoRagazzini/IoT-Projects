#include "SingleMode.h"


SingleMode::SingleMode(int pin, Scan* s, PirDetectionTask* pir, ReadPotTask* pot){
    Mode::attachButton(pin);
    this->s = s;
    this->pir = pir;
    this->pot = pot;
}

void SingleMode::switchOn(){
    this->s->setActive(false);
    this->s->init(125);
    this->pir->setActive(true);
    this->pot->setActive(true);
   
}

void SingleMode::switchOff(){
    this->s->setActive(false);
    this->s->switchRadarOff();
    this->pir->setActive(false);
    this->pot->setActive(false);
}
