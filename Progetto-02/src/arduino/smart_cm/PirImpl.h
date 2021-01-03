#ifndef __PIR_IMPL__
#define __PIR_IMPL__
#include "Pir.h"

class PirImpl : public Pir{

    public:

        PirImpl(int pin);
        void calibrate();
        int hasDetected();

    private:

        int pin;
        const int calibrationTimeSec = 3;
};

#endif
