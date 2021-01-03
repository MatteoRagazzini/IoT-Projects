#include "AutoScanTask.h"
#include "MsgService.h"

AutoScanTask::AutoScanTask(int echoPin, int trigPin, int servoPin, BlinkTask* Ld, BlinkTask* b, TrackingTask* t): Scan(echoPin, trigPin, servoPin, Ld) {
  this->b = b;
  this->t = t;
  this->alarmState = false;
}

void AutoScanTask::scanOver() {
  if (!this->alarmState) {
    b->setActive(false);
    b->switchOff();
    MsgService.sendMsg("A0");
  }
  this->alarmState = false;
}

void AutoScanTask::checkAlarm() {
  if (radar->inAlarm() || radar->inAlarmWithTracking() ) {
    b->setActive(true);
    b->init(125);
    MsgService.sendMsg("A1");
    this->alarmState = true;
    if (radar->inAlarmWithTracking()) {
      setActive(false);
      t->setActive(true);
      t->attachScan(this);
      t->setRadar(radar);
    }
  }
}
