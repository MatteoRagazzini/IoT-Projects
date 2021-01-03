#ifndef __SINGLESCAN__
#define __SINGLESCAN__

#include "Scan.h"

class SingleScanTask : public Scan {

    public:
    SingleScanTask(int echoPin, int trigPin, int servoPin, BlinkTask* Ld);

    private:
     void scanOver();
     void checkAlarm();

};

#endif
