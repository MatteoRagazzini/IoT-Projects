#ifndef __AUTOSCANTASK__
#define __AUTOSCANTASK__

#include "Scan.h"
#include "BlinkTask.h"
#include "TrackingTask.h"

class AutoScanTask : public Scan {

    BlinkTask* b;
    TrackingTask* t;
    bool alarmState;



    public:
    AutoScanTask(int echoPin, int trigPin, int servoPin, BlinkTask* Ld, BlinkTask* b, TrackingTask* t);

    private:
     void scanOver();
     void checkAlarm();

};

#endif
