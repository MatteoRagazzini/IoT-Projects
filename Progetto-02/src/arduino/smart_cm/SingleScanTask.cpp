#include "SingleScanTask.h"

 SingleScanTask::SingleScanTask(int echoPin, int trigPin, int servoPin,  BlinkTask* Ld):Scan(echoPin, trigPin, servoPin, Ld){}

void SingleScanTask::scanOver(){
     setActive(false);
 }

 void SingleScanTask::checkAlarm(){}
