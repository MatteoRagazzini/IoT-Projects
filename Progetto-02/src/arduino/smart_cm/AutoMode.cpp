#include "AutoMode.h"

AutoMode::AutoMode(int pin, Scan* s, ReadPotTask* p, BlinkTask* b, TrackingTask* t){
    Mode::attachButton(pin);
    this->s = s;
    this->pot = p;
    this->b = b;
    this->t = t;
}

void AutoMode::switchOn(){
    this->s->setActive(true);
    this->s->init(125);
    this->pot->setActive(true);
    this->b->setActive(false);
    this->t->setActive(false);
}

void AutoMode::switchOff(){
    this->s->setActive(false);
    this->s->switchRadarOff();
    this->pot->setActive(false);
    this->b->setActive(false);
    this->b->switchOff();
    this->t->setActive(false);
    
}
