#ifndef __AUTOMODE__
#define __AUTOMODE__

#include "Mode.h"
#include "Scan.h"
#include "ReadPotTask.h"
#include "BlinkTask.h"
#include "TrackingTask.h"

class AutoMode: public Mode {

    Scan* s;
    ReadPotTask *pot;
    BlinkTask* b;
    TrackingTask* t; 


public:
    AutoMode(int pin, Scan* s , ReadPotTask* p, BlinkTask* b, TrackingTask* t);
    void switchOn();
    void switchOff();
};

#endif
