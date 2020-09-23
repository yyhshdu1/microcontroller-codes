#include "Arduino.h"
#include "displayControl.h"
#include "symbols.h"

DisplayControl::DisplayControl(Adafruit_SSD1306 *display, MTD415State *mtd415_state){
  _display = (Adafruit_SSD1306 *)display;
  _mtd415_state = (MTD415State *)mtd415_state;
  display_state = 0;
  display_toggle = 1;
  display_state_max = 3;
  _display_time = millis();
  _display_time_length = 4000;
  _devices = _mtd415_state->devices;
}

void DisplayControl::displayCeNTREXLogo(){
  _display->clearDisplay();
  _display->drawBitmap(64-50,0, CeNTREX_logo, 100, 64, SSD1306_WHITE);
  _display->display();
}

void DisplayControl::updateDisplay(){
  switch(display_state){
    case 0:
      this->updateDisplayTemperature();
      break;
    case 1:
      this->updateDisplayTemperatureSetpoint();
      break;
    case 2:
      this->updateDisplayTECCurrentLimit();
      break;
    case 3:
      this->updateDisplayTECCurrentActual();
      break;
  }
}

void DisplayControl::_displayData(float * data){
  bool enabled[_devices];
  _mtd415_state->getEnabled(enabled);
  if (_prev_display_state != display_state){
    _prev_display_state = display_state;
    display_toggle = 0;
    _display_time = millis();
  }
  if (millis() - _display_time > _display_time_length){
    display_toggle = !display_toggle;
    _display_time = millis();
  }
  if (_devices > 2){
    switch(display_toggle){
      case 0:
        for (int dev = 0; dev < _devices; dev++){
          _display->setCursor(0,25*(dev+1));
          _display->print(dev+1);
          _display->print(": ");
          _display->print(data[dev],3);
          if (enabled[dev] == false){
            _display->setCursor(128-6*2,25*(dev+1));
            _display->print("O");
          }
          else{
            _display->setCursor(128-6*2,25*(dev+1));
            _display->print("I");
          }
        }
        break;
      case 1:
          for (int dev = 2; dev < _devices; dev++){
            _display->setCursor(0,25*(dev - 1));
            _display->print(dev+1);
            _display->print(": ");
            _display->print(data[dev],3);
          if (enabled[dev] == false){
            _display->setCursor(128-6*2,25*(dev-1));
            _display->print("O");
          }
          else{
            _display->setCursor(128-6*2,25*(dev+1));
            _display->print("I");
          }
        }
        break;
    }
  }
  else{
    for (int dev = 0; dev < _devices; dev++){
      _display->setCursor(0,25*(dev+1));
      _display->print(dev+1);
      _display->print(": ");
      _display->print(data[dev],3);
      if (enabled[dev] == false){
        _display->setCursor(128-6*2,25*(dev+1));
        _display->print("O");
      }
      else{
        _display->setCursor(128-6*2,25*(dev+1));
        _display->print("I");
      }
    }
  }
  _display->display();
}

void DisplayControl::_displayData(int * data){
  bool enabled[_devices];
  _mtd415_state->getEnabled(enabled);
  if (_prev_display_state != display_state){
    _prev_display_state = display_state;
    display_toggle = 0;
    _display_time = millis();
  }
  if (millis() - _display_time > _display_time_length){
    display_toggle = !display_toggle;
    _display_time = millis();
  }
  if (_devices > 2){
    switch(display_toggle){
      case 0:
        for (int dev = 0; dev < _devices; dev++){
          _display->setCursor(0,25*(dev+1));
          _display->print(dev+1);
          _display->print(": ");
          _display->print(data[dev]);
          if (enabled[dev] == false){
            _display->setCursor(128-6*2,25*(dev+1));
            _display->print("O");
          }
          else{
            _display->setCursor(128-6*2,25*(dev+1));
            _display->print("I");
          }
        }
        break;
      case 1:
          for (int dev = 2; dev < _devices; dev++){
            _display->setCursor(0,25*(dev - 1));
            _display->print(dev+1);
            _display->print(": ");
            _display->print(data[dev]);
          if (enabled[dev] == false){
            _display->setCursor(128-6*2,25*(dev-1));
            _display->print("O");
          }
          else{
            _display->setCursor(128-6*2,25*(dev+1));
            _display->print("I");
          }
        }
        break;
    }
  }
  else{
    for (int dev = 0; dev < _devices; dev++){
      _display->setCursor(0,25*(dev+1));
      _display->print(dev+1);
      _display->print(": ");
      _display->print(data[dev]);
      if (enabled[dev] == false){
        _display->setCursor(128-6*2,25*(dev+1));
        _display->print("O");
      }
      else{
       _display->setCursor(128-6*2,25*(dev+1));
       _display->print("I");
      }
    }
  }
  _display->display();
}

void DisplayControl::updateDisplayTemperature(){
  _display->clearDisplay();
  _display->setTextSize(2);
  _display->setTextColor(SSD1306_WHITE);
  _display->setCursor(0, 0);
  _display->println("Temp Act");

  int temperature[_devices];
  _mtd415_state->getTemperature(temperature);
  float temperature_float[_devices];
  for (int dev = 0; dev < _devices; dev++){
    temperature_float[dev] = float(temperature[dev])/1000;
  }
  this->_displayData(temperature_float);
}

void DisplayControl::updateDisplayTemperatureSetpoint(){
  _display->clearDisplay();
  _display->setTextSize(2);
  _display->setTextColor(SSD1306_WHITE);
  _display->setCursor(0, 0);
  _display->println("Temp Set");

  int temperature[_devices];
  _mtd415_state->getTemperatureSetpoint(temperature);
  float temperature_float[_devices];
  for (int dev = 0; dev < _devices; dev++){
    temperature_float[dev] = float(temperature[dev])/1000;
  }
  this->_displayData(temperature_float);
}

void DisplayControl::updateDisplayTECCurrentLimit(){
  _display->clearDisplay();
  _display->setTextSize(2);
  _display->setTextColor(SSD1306_WHITE);
  _display->setCursor(0, 0);
  _display->println("TEC Limit");

  int current_limit[_devices];
  _mtd415_state->getTECCurrentLimit(current_limit);
  this->_displayData(current_limit);
}

void DisplayControl::updateDisplayTECCurrentActual(){
  _display->clearDisplay();
  _display->setTextSize(2);
  _display->setTextColor(SSD1306_WHITE);
  _display->setCursor(0, 0);
  _display->println("TEC Curr");

  int current[_devices];
  _mtd415_state->getTECCurrentActual(current);
  this->_displayData(current);
}
