#ifndef debounce_h
#define debounce_h
#include "Arduino.h"

class Button
{
  public:
    Button(int button, unsigned long debounceDelay);
    int getStateChange();
    int getState();
  private:
    int _button;
    int _previous;
    int _state;
    long _time;
    int _debounceDelay;
};

#endif
