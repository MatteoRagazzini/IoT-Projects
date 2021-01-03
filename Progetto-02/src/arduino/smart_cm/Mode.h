#ifndef __MODE__
#define __MODE__

#include "ButtonImpl.h"

class Mode {
  
  Button* button;
 
public: 

void attachButton(int pin){
    this->button = new ButtonImpl(pin);
}

bool isActive(){
    return this->button->isPressed();
}

virtual void switchOn() = 0;
virtual void switchOff() = 0;

};

#endif
