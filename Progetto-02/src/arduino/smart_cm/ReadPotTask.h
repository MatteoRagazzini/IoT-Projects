#ifndef __READPOTTASK__
#define __READPOTTASK__

#include "Task.h"
#include "PotImpl.h"
#include "Scan.h"
#include "MyPattern.h"

class ReadPotTask: public Task {

PotImpl* pot;
Scan* s;
Pattern* p ;
int lastMecanicPotValue;
int lastSerialPotValue;

public:

  ReadPotTask(int pin, Scan*s);  
  void init(int period);  
  void tick();
};

#endif
