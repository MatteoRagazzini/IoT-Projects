/*Led to Bag 
  Authors: Matteo Ragazzini, Marta Spadoni*/
#include "LedToBag.h"

void setup() {
  setAll();
}

void loop() {
  if(!isInGame()){
    blinkingFase();
  }else{
    if(hasLose()){
      gameOver();
    }
    if(inBag()){
      fade();
      if(fadeCompleted()){
        nextTurn();
       }
    }
  }
}
