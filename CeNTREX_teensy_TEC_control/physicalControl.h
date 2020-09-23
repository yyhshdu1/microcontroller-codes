#ifndef physicalcontrol_h
#define physicalcontrol_h

#include "Arduino.h"
#include "MTD415.h"
#include "MTD415State.h"
#include "displayControl.h"
#include <Bounce2.h>



class PhysicalControl{
  public:
    PhysicalControl(MTD415State *mtd415_state, DisplayControl *display_ctrl, int * enable, int * enable_buttons, int display_cycle_button);
    void setup();
    void setEnable(int * arr);
    void handlePhysical();
    void toggleEnable(int dev);
  private:
    DisplayControl *_display_ctrl;
    MTD415State *_mtd415_state;
    Bounce _display_cycle_button;
    Bounce _enable_buttons[4];
    int _enable_state[4];
    int _enable[4];
    int _devices;
    int _display_state_max;
};

#endif
