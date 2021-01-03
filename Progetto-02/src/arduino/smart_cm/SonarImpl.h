#ifndef __SONAR_IMPL__
#define __SONAR_IMPL__
#include "Sonar.h"

class SonarImpl : public Sonar{

    public:

        SonarImpl(int echoPin, int trigPin);
        float getDistance();

    private:

        int echoPin;
        int trigPin;
        /* supponendo di eseguire il test 
        in un ambiente a 20 °C 
        https://it.wikipedia.org/wiki/Velocità_del_suono
        */ 
        const double vs = 331.45 + 0.62*20;
};

#endif
