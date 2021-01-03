#ifndef __MANUALMODE__
#define __MANUALMODE__

#include "Mode.h"
#include "ManualScanTask.h"

class ManualMode: public Mode {

    ManualScanTask* s;


public:
    ManualMode(int pin, ManualScanTask* s );
    void switchOn();
    void switchOff();
};

#endif
