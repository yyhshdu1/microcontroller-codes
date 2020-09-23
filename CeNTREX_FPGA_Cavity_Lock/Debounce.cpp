#include "Arduino.h"
#include "debounce.h"

Button::Button(int button, unsigned long debounceDelay){
  _button = button;
  _debounceDelay = debounceDelay;
  _previous = LOW;
  _state = HIGH;
  _time = 0;
  pinMode(_button, INPUT);
}

int Button::getStateChange(){
  int reading = digitalRead(_button);
  if (reading == HIGH && _previous == LOW && millis() - _time > _debounceDelay){
    _time = millis();
    _previous = HIGH;
    return HIGH;
  }
  _previous = reading;
  return LOW;
}
