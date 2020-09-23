#include "Arduino.h"
#include "state.h"

State::State(int in1, int in2, int out1, int out2){
  _in1 = in1;
  _in2 = in2;
  _out1 = out1;
  _out2 = out2;
  pinMode(_in1, INPUT);
  pinMode(_in2, INPUT);
  pinMode(_out1, OUTPUT);
  pinMode(_out2, OUTPUT);
}

void State::getState(){
  int in1 = digitalRead(_in1);
  int in2 = digitalRead(_in2);
  // off
  if (in1 == LOW && in2 == LOW) 
  {
    lockState = LOW;
    lockedState = LOW;
    scanState = LOW;
  }
  // scanning
  else if (in1 == HIGH && in2 == LOW){
    lockState = LOW;
    lockedState = LOW;
    scanState = HIGH;
  }
  // locking
  else if (in1 == LOW && in2 == HIGH){
    lockState = HIGH;
    lockedState = LOW;
    scanState = LOW;
  }
  // locked
  else if (in1 == HIGH && in2 == HIGH){
    lockState = HIGH;
    lockedState = HIGH;
    scanState = LOW;
  }
}

void State::writeScan(int scan){
  this->getState();
  // check if scan state is different
  if (scanState != scan){
    if (scanState == HIGH){
      digitalWrite(_out1, LOW);
      digitalWrite(_out2, LOW);
    }
    else if (scanState == LOW){
      digitalWrite(_out1, HIGH);
      digitalWrite(_out2, LOW);
    }
  }
}

void State::toggleScan(){
  this->getState();
  this->writeScan(!scanState);
}

void State::writeLock(int lock){
  this->getState();
  // check if lock state is different
  if (lockState != lock){
    // if locked, unlock
    if (lockState == HIGH){
      digitalWrite(_out1, HIGH);
      digitalWrite(_out2, LOW);
    }
    // if unlocked, lock
    else if (lockState == LOW){
      digitalWrite(_out1, HIGH);
      digitalWrite(_out2, HIGH);
    }
  }
}

void State::toggleLock(){
  this->getState();
  this->writeLock(!lockState);
}
