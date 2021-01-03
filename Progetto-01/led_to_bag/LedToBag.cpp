#include <Arduino.h>
#include "MiniTimerOne.h"
#define LED_NUMBER 5
#define WHITE_LED_POSITION 3
#define RED_LED_POSITION 4
#define TS_PIN 3
#define TD_PIN 2
#define POT_PIN A0
#define BOUNCING_TIME 150000
//the array to handle all the leds and their pins
int pinLed[LED_NUMBER] = {13, 12, 8, 6, 4};
//the Led that is currently high
int currentLed = 0;
int inc = 1;
bool inGame = false;
bool welcomeFase = true;
bool fadeComplete = false;
bool lose = false;
//Timer's period
unsigned long DT = 0;
//utility variable to check the bouncing time
long prev = 0;
//utility variables for fading
int currentIntensity = 0;
int delta = 5;
//score
int count = 0;

//interrupt function called when timer expired
void timerGameOver() {
  lose = true;
}
//function to turn all led off
void allOff() {
  for (int i = 0; i < LED_NUMBER; i++) {
    digitalWrite(pinLed[i], LOW);
  }
}
void turnOnRandomLed() {
  allOff();
  currentLed = random(3);
  digitalWrite(pinLed[currentLed], HIGH);
}

void setTimer(){
  MiniTimer1.stop();
  MiniTimer1.reset();
  MiniTimer1.setPeriod(DT);
  MiniTimer1.attachInterrupt(timerGameOver);
  MiniTimer1.start();
}
//Interrupt function to handle the start of the game
void startGame() {
  if (!inGame) {
    inGame = true;
    Serial.println("Go!");
    //read from pot the value(0-1023)
    int difficulty = analogRead(POT_PIN);
    //we mapped all the 1024 values of the pot in 8 levels by dividing them by 127 (1023/8=127)
    //as the difficulty increases, the time available to carry an object in the bag deacreases
    //1st level = 4s, 8th level = 1,6s
    DT = 4000000 - difficulty / 127 * 300000;
    setTimer();
    turnOnRandomLed();
  }
}
//interrupt function for TD buttom
void goDown() {
  long now = micros();
  //check that the game is started, that it is not an interrupt due to the bouncing effect and that the player has not already lost
  if (inGame && now - prev >= BOUNCING_TIME && !lose) {
    allOff();
    prev = now;
    //noInterrupts();
    currentLed++;
    //interrupts();
    currentLed = currentLed >= RED_LED_POSITION ? RED_LED_POSITION : currentLed;
    digitalWrite(pinLed[currentLed], HIGH);
    EIFR = _BV(INTF0);
  }
}
void setAll() {
  Serial.begin(9600);
  for (int i = 0; i < LED_NUMBER; i++) {
    pinMode(pinLed[i], OUTPUT);
  }
  MiniTimer1.init();
  attachInterrupt(digitalPinToInterrupt(TS_PIN), startGame, RISING);
  attachInterrupt(digitalPinToInterrupt(TD_PIN), goDown, RISING);
  randomSeed(analogRead(0));
}


void blinkingFase() {
  if (welcomeFase) {
    Serial.println("Welcome to Led to Bag. Press Key TS to Start");
    welcomeFase = false;
  }
  allOff();
  digitalWrite(pinLed[currentLed], HIGH);
  currentLed += inc;
  if (currentLed == 3 || currentLed == -1) {
    inc = -inc;
    currentLed = currentLed == 3 ? 2 : 0;
  }
  delay(200);
}
//function called when the object was carried in the bag to start a new round
void nextTurn() {
  fadeComplete = false;
  DT = DT * 7 / 8;
  setTimer();
  turnOnRandomLed();
}
bool isInGame() {
  return inGame;
}
bool hasLose() {
  return currentLed >= RED_LED_POSITION || lose;
}

bool inBag() {
  return currentLed == WHITE_LED_POSITION;
}

bool fadeCompleted(){
  return fadeComplete;
}

void fade() {
  MiniTimer1.stop();
  analogWrite(pinLed[WHITE_LED_POSITION], currentIntensity);
  currentIntensity += delta;
  if (currentIntensity >= 255) {
    delta = - delta;
  } else if (currentIntensity <= 0) {
    delta = - delta;
    count++;
    analogWrite(pinLed[WHITE_LED_POSITION], currentIntensity);
    Serial.println("Another object in the bag! Count: " + String(count) + " objects");
    fadeComplete = true;
  }
  delay(20);
}
void resetAll() {
  welcomeFase = true;
  inGame = false;
  lose = false;
  fadeComplete = false;
  currentLed = 0;
  currentIntensity = 0;
  delta = 5;
  count = 0;
}

void gameOver() {
  MiniTimer1.stop();
  allOff();
  digitalWrite(pinLed[RED_LED_POSITION], HIGH);
  Serial.println("Game Over - Score: " + String(count));
  resetAll();
  delay(2000);

}
