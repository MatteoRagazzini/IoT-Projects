#include "PirDetectionTask.h"
#include "Arduino.h"
#include <avr/sleep.h>
#include <avr/power.h>

void goToSleep(){
    set_sleep_mode(SLEEP_MODE_IDLE); // sleep mode is set here
    sleep_enable(); // enables the sleep bit in the mcucr register
    power_adc_disable();
    power_spi_disable();
    power_timer0_disable(); // only timer 1
    power_timer2_disable(); // on
    //power_timer1_disable();
    power_twi_disable();
    //Serial.println("Go to sleep");
    sleep_mode(); // here the device is actually put to sleep!!
    // THE PROGRAM CONTINUES FROM HERE AFTER WAKING UP
    sleep_disable(); // first thing after waking from sleep:
    power_all_enable();
    // disable sleep...
}

PirDetectionTask::PirDetectionTask(int pin, Task* s){
  this->pir = new PirImpl(pin); 
  this->s = s;
}
  
void PirDetectionTask::init(int period){
  Task::init(period);
  this->pir->calibrate();
}
  
void PirDetectionTask::tick(){
  if(!s->isActive()){
    if(this->pir->hasDetected()){
      this->s->setActive(true);
    }else{
      goToSleep();
    }
  }
}
