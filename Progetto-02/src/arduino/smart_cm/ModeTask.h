#ifndef __MODETASK__
#define __MODETASK__

#include "Mode.h"
#include "MyPattern.h"
#include "Task.h"
#define MAX_MODES 5

class ModeTask: public Task {

    Mode* modes[MAX_MODES];
    int currentMode;
    int nModes;
    Pattern *p;

public:
    ModeTask();
    void addMode(Mode* m);
    void init(int period);  
    void tick();
};

#endif
