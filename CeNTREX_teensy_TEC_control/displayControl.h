#ifndef displaycontrol_h
#define displaycontrol_h

#include "Arduino.h"
#include "MTD415.h"
#include "MTD415State.h"
#include <Adafruit_SSD1306.h>

class DisplayControl{
  public:
    DisplayControl(Adafruit_SSD1306 *display, MTD415State *mtd415_state);
    void displayCeNTREXLogo();
    void updateDisplay();
    void updateDisplayTemperature();
    void updateDisplayTemperatureSetpoint();
    void updateDisplayTECCurrentLimit();
    void updateDisplayTECCurrentActual();
    int display_toggle;
    int display_state;
    int display_state_max;
  private:
    Adafruit_SSD1306 *_display;
    MTD415State *_mtd415_state;
    // _display_state numbers are:
    // 0 -> temperature
    // 1 -> temperature setpoint
    // 2 -> tec current limit
    // 3 -> tec current actual
    // 4 -> tec voltage
    int _prev_display_state;
    long _display_time;
    int _display_time_length;
    void _displayData(int * data);
    void _displayData(float * data);
    int _devices;
};

#endif
