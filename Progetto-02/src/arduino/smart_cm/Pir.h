#ifndef __PIR__
#define __PIR__

class Pir{

    public:
        virtual void calibrate() = 0;
        virtual int hasDetected() = 0;   
};

#endif