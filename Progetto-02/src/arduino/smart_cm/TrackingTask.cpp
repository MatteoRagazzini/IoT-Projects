#include "TrackingTask.h"
#include "Arduino.h"

  TrackingTask::TrackingTask(){
    
  }  
  void TrackingTask::init(int period){
    Task::init(period);
  }
  void TrackingTask::tick(){
    if(r->inAlarmWithTracking()){
      this->r->scan();
    }else{
      setActive(false);
      this->s->setActive(true);
    }
  }
  void TrackingTask::attachScan(Scan* s){
    this->s=s;
  }

  void TrackingTask::setRadar(RadarImpl* r){
    this->r=r;
  }
