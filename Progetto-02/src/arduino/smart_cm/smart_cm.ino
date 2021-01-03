#include "Scheduler.h"
#include "SingleScanTask.h"
#include "AutoScanTask.h"
#include "BlinkTask.h"
#include "PirDetectionTask.h"
#include "ReadPotTask.h"
#include "ManualScanTask.h"
#include "ManualMode.h"
#include "ModeTask.h"
#include "Mode.h"
#include "SingleMode.h"
#include "AutoMode.h"
#include "MsgService.h"

Scheduler sched;

void setup(){

  Serial.begin(9600);
  sched.init(125);
  
  MsgService.init();
  
  Task* Ld = new BlinkTask(13, false);
  Ld->init(50);
  Ld->setActive(false);
  sched.addTask(Ld);
  
  Task* t1 = new SingleScanTask(7,8,2,(BlinkTask*)Ld);
  t1->init(125);
  sched.addTask(t1);
  
  Task* t2 = new ReadPotTask(A0,(Scan*)t1);
  t2->init(125);
  sched.addTask(t2);
  
  Task* t3 = new PirDetectionTask(11, t1);
  t3->init(125);
  sched.addTask(t3);

  Task* ms = new ManualScanTask(7,8,2,(BlinkTask*)Ld);
  ms->init(125);
  sched.addTask(ms);

  Task* t4 = new BlinkTask(12, true);
  t4->init(250);
  sched.addTask(t4);

  Task* t5 = new TrackingTask();
  t5->init(125);
  sched.addTask(t5);
  
  Task* t7 = new AutoScanTask(7,8,2,(BlinkTask*)Ld, (BlinkTask*)t4, (TrackingTask*)t5);
  t7->init(125);
  sched.addTask(t7);
  
  Task* t6 = new ReadPotTask(A0,(Scan*)t7);
  t6->init(125);
  sched.addTask(t6);
  
  Mode* single = new SingleMode(3, (Scan*)t1, (PirDetectionTask*)t3, (ReadPotTask*)t2);
  Mode* autoMode = new AutoMode(4, (Scan*)t7, (ReadPotTask*)t6, (BlinkTask*)t4, (TrackingTask*)t5);
  Mode* manual = new ManualMode(5,(ManualScanTask*)ms);
  
  ModeTask* mt = new ModeTask();
  mt->addMode(single);
  mt->addMode(autoMode);
  mt->addMode(manual);
  mt->init(125);
  mt->setActive(true);
  sched.addTask((Task*)mt);
  
  manual->switchOff();
  single->switchOff();
  autoMode->switchOff();
  manual->switchOn();
  
    
}

void loop(){
  sched.schedule();
}
