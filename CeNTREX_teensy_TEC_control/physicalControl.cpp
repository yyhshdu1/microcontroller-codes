#include "Arduino.h"
#include "physicalControl.h"

PhysicalControl::PhysicalControl(MTD415State *mtd415_state, DisplayControl *display_ctrl, int * enable, int * enable_buttons, int display_cycle_button){
  _mtd415_state = (MTD415State *)mtd415_state;
  _display_ctrl = (DisplayControl *)display_ctrl;
  _display_cycle_button.attach(display_cycle_button, INPUT_PULLUP);
  _display_cycle_button.interval(5);
  _devices = _mtd415_state->devices;
  for (int dev = 0; dev < _devices; dev++){
    _enable[dev] = enable[dev];
    _enable_buttons[dev].attach(enable_buttons[dev], INPUT_PULLUP);
    _enable_buttons[dev].interval(5);
  }
  _display_state_max = _display_ctrl->display_state_max;
}

void PhysicalControl::setup(){
  for (int dev = 0; dev < _devices; dev++){
    pinMode(_enable[dev], OUTPUT);
    digitalWrite(_enable[dev], HIGH);
    _enable_state[dev] = 0;
  }
}

void PhysicalControl::setEnable(int * arr){
  for (int dev = 0; dev < _devices; dev++){
    digitalWrite(_enable[dev], !arr[dev]);
    _enable_state[dev] = arr[dev];
  }
}

void PhysicalControl::toggleEnable(int dev){
  digitalWrite(_enable[dev], !_enable_state[dev]);
  _enable_state[dev] = !_enable_state[dev];
}

void PhysicalControl::handlePhysical(){
  _display_cycle_button.update();
  
  if (_display_cycle_button.fell()){
    if (_display_ctrl->display_state == _display_state_max){
      _display_ctrl->display_state = 0;
    }
    else{
      _display_ctrl->display_state++;
    } 
  }
  
  for (int dev = 0; dev < _devices; dev++){
    _enable_buttons[dev].update();
    
    if (_enable_buttons[dev].fell()){
      this->toggleEnable(dev);
    }
  }
}
