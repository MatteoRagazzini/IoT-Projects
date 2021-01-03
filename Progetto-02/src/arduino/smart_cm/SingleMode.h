
#ifndef __SINGLEMODE__
#define __SINGLEMODE__

#include "Mode.h"
#include "Scan.h"
#include "ReadPotTask.h"
#include "PirDetectionTask.h"

class SingleMode: public Mode {

    Scan* s;
    PirDetectionTask* pir;
    ReadPotTask* pot;


public:
    SingleMode(int pin, Scan* s, PirDetectionTask* pir, ReadPotTask* pot);
    void switchOn();
    void switchOff();
};

#endif
