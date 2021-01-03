#include "Servo_motor_impl.h"

ServoMotorImpl::ServoMotorImpl(int pin){
  this->pin = pin;
  this->angle = 0; 
} 

void ServoMotorImpl::on(){
  motor.attach(pin); 
     
}

void ServoMotorImpl::setPosition(int newAngle){
  this->angle = 750 + newAngle*coeff;
  motor.write(angle);              
}

int ServoMotorImpl::getPosition(){
  return (this->angle-750)/coeff;
}

void ServoMotorImpl::off(){
  motor.detach();    
}
