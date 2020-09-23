#include "Arduino.h"
#include "MTD415.h"
#include "MTD415State.h"

MTD415State::MTD415State(MTD415 *control_1, MTD415 *control_2, MTD415 *control_3, MTD415 *control_4){
  devices = 4;
  _devices = 4;
  _connections.nrdevices = 4;
  _connections.devices[0] = control_1;
  _connections.devices[1] = control_2;
  _connections.devices[2] = control_3;
  _connections.devices[3] = control_4;
  _bitmask = 255;
}

MTD415State::MTD415State(MTD415 *control_1, MTD415 *control_2, MTD415 *control_3){
  devices = 3;
  _devices = 3;
  _connections.nrdevices = 3;
  _connections.devices[0] = control_1;
  _connections.devices[1] = control_2;
  _connections.devices[3] = control_3;
  _bitmask = 255;
}

MTD415State::MTD415State(MTD415 *control_1, MTD415 *control_2){
  devices = 2;
  _devices = 2;
  _connections.nrdevices = 2;
  _connections.devices[0] = control_1;
  _connections.devices[1] = control_2;
  _bitmask = 255;
}

MTD415State::MTD415State(MTD415 *control){
  devices = 1;
  _devices = 1;
  _connections.nrdevices = 1;
  _connections.devices[0] = control;
  _bitmask = 255;
}

// General

void MTD415State::updateVersion(){
  for (int dev = 0; dev < _devices; dev++){
    _version[dev] = _connections.devices[dev]->getVersion();
  }
}

void MTD415State::getVersion(String * arr){
  for (int dev = 0; dev < _devices; dev++){
    arr[dev] = _version[dev];
  }
}

void MTD415State::updateUUID(){
  for (int dev = 0; dev < _devices; dev++){
    _uuid[dev] = _connections.devices[dev]->getUUID();
  }
}

void MTD415State::getUUID(String * arr){
  for (int dev = 0; dev < _devices; dev++){
    arr[dev] = _uuid[dev];
  }
}

void MTD415State::updateErrorRegister(){
  int error;
  for (int dev = 0; dev < _devices; dev++){
    error = _connections.devices[dev]->getErrorRegister();
    _error[dev] = error;
    _enabled[dev] = !bool(error & _bitmask);
  }
}

void MTD415State::getErrorRegister(int * arr){
  for (int dev = 0; dev < _devices; dev++){
    arr[dev] = _error[dev];
  }
}

void MTD415State::resetErrorRegister(int device){
  _connections.devices[device]->resetErrorRegister();
}

// Temperature commands

void MTD415State::updateTemperature(){
  for (int dev = 0; dev < _devices; dev++){
    _temperature[dev] = _connections.devices[dev]->getTemperature();
  }
}

void MTD415State::getTemperature(int * arr){
  for (int dev = 0; dev < _devices; dev++){
    arr[dev] = _temperature[dev];
  }
}

int MTD415State::getTemperature(int dev){
  if (dev >= _devices){
    return -1;
  }
  return _temperature[dev];
}

void MTD415State::updateTemperatureSetpoint(){
  for (int dev = 0; dev < _devices; dev++){
    _temperature_setpoint[dev] = _connections.devices[dev]->getTemperatureSetpoint();
  }
}

void MTD415State::getTemperatureSetpoint(int * arr){
  for (int dev = 0; dev < _devices; dev++){
    arr[dev] = _temperature_setpoint[dev];
  }
}

int MTD415State::getTemperatureSetpoint(int dev){
  if (dev >= _devices){
    return -1;
  }
  return _temperature_setpoint[dev];
}

void MTD415State::setTemperatureSetpoint(int * arr){
  for (int dev = 0; dev < _devices; dev++){
    _connections.devices[dev]->setTemperatureSetpoint(arr[dev]);
  }
  this->updateTemperatureSetpoint();
}

void MTD415State::updateTemperatureWindow(){
  for (int dev = 0; dev < _devices; dev++){
    _temperature_window[dev] = _connections.devices[dev]->getTemperatureWindow();
  }
}

void MTD415State::getTemperatureWindow(int * arr){
  for (int dev = 0; dev < _devices; dev++){
    arr[dev] = _temperature_window[dev];
  }
}

int MTD415State::getTemperatureWindow(int dev){
  if (dev >= _devices){
    return -1;
  }
  return _temperature_window[dev];
}

void MTD415State::setTemperatureWindow(int * arr){
  for (int dev = 0; dev < _devices; dev++){
    _connections.devices[dev]->setTemperatureWindow(arr[dev]);
  }
  this->updateTemperatureWindow();
}

void MTD415State::updateTemperatureWindowDelay(){
  for (int dev = 0; dev < _devices; dev++){
    _temperature_window_delay[dev] = _connections.devices[dev]->getTemperatureWindowDelay();
  }
}

void MTD415State::getTemperatureWindowDelay(int * arr){
  for (int dev = 0; dev < _devices; dev++){
    arr[dev] = _temperature_window_delay[dev];
  }
}

int MTD415State::getTemperatureWindowDelay(int dev){
  if (dev >= _devices){
    return -1;
  }
  return _temperature_window_delay[dev];
}

void MTD415State::setTemperatureWindowDelay(int * arr){
  for (int dev = 0; dev < _devices; dev++){
    _connections.devices[dev]->setTemperatureWindowDelay(arr[dev]);
  }
  this->updateTemperatureWindowDelay();
}

// TEC commands

void MTD415State::updateTECCurrentLimit(){
  for (int dev = 0; dev < _devices; dev++){
    _tec_current_limit[dev] = _connections.devices[dev]->getTECCurrentLimit();
  }
}

void MTD415State::getTECCurrentLimit(int * arr){
  for (int dev = 0; dev < _devices; dev++){
    arr[dev] = _tec_current_limit[dev];
  }
}

int MTD415State::getTECCurrentLimit(int dev){
  if (dev >= _devices){
    return -1;
  }
  return _tec_current_limit[dev];
}

void MTD415State::updateTECCurrentActual(){
  for (int dev = 0; dev < _devices; dev++){
    _tec_current_actual[dev] = _connections.devices[dev]->getTECCurrentActual();
  }
}

void MTD415State::getTECCurrentActual(int * arr){
  for (int dev = 0; dev < _devices; dev++){
    arr[dev] = _tec_current_actual[dev];
  }
}

int MTD415State::getTECCurrentActual(int dev){
  if (dev >= _devices){
    return -1;
  }
  return _tec_current_actual[dev];
}

void MTD415State::updateTECVoltage(){
  for (int dev = 0; dev < _devices; dev++){
    _tec_voltage[dev] = _connections.devices[dev]->getTECVoltage();
  }
}

void MTD415State::getTECVoltage(int * arr){
  for (int dev = 0; dev < _devices; dev++){
    arr[dev] = _tec_voltage[dev];
  }
}

int MTD415State::getTECVoltage(int dev){
  if (dev >= _devices){
    return -1;
  }
  return _tec_voltage[dev];
}

void MTD415State::setTECCurrentLimit(int * arr){
  for (int dev = 0; dev < _devices; dev++){
    _connections.devices[dev]->setTECCurrentLimit(arr[dev]);
  }
  this->updateTECCurrentLimit();
}

// Control loop

void MTD415State::updateCriticalGain(){
  for (int dev = 0; dev < _devices; dev++){
    _critical_gain[dev] = _connections.devices[dev]->getCriticalGain();
  }
}

void MTD415State::getCriticalGain(int * arr){
  for (int dev = 0; dev < _devices; dev++){
    arr[dev] = _critical_gain[dev];
  }
}

int MTD415State::getCriticalGain(int dev){
  if (dev >= _devices){
    return -1;
  }
  return _critical_gain[dev];
}

void MTD415State::updateCriticalPeriod(){
  for (int dev = 0; dev < _devices; dev++){
    _critical_period[dev] = _connections.devices[dev]->getCriticalGain();
  }
}

void MTD415State::getCriticalPeriod(int * arr){
  for (int dev = 0; dev < _devices; dev++){
    arr[dev] = _critical_period[dev];
  }
}

int MTD415State::getCriticalPeriod(int dev){
  if (dev >= _devices){
    return -1;
  }
  return _critical_period[dev];
}

void MTD415State::updateCyclingTime(){
  for (int dev = 0; dev < _devices; dev++){
    _cycling_time[dev] = _connections.devices[dev]->getCyclingTime();
  }
}

void MTD415State::getCyclingTime(int * arr){
  for (int dev = 0; dev < _devices; dev++){
    arr[dev] = _cycling_time[dev];
  }
}

int MTD415State::getCyclingTime(int dev){
  if (dev >= _devices){
    return -1;
  }
  return _cycling_time[dev];
}

void MTD415State::updateProportional(){
  for (int dev = 0; dev < _devices; dev++){
    _proportional[dev] = _connections.devices[dev]->getProportional();
  }
}

void MTD415State::getProportional(int * arr){
  for (int dev = 0; dev < _devices; dev++){
    arr[dev] = _proportional[dev];
  }
}

int MTD415State::getProportional(int dev){
  if (dev >= _devices){
    return -1;
  }
  return _proportional[dev];
}

void MTD415State::updateIntegral(){
  for (int dev = 0; dev < _devices; dev++){
    _integral[dev] = _connections.devices[dev]->getIntegral();
  }
}

void MTD415State::getIntegral(int * arr){
  for (int dev = 0; dev < _devices; dev++){
    arr[dev] = _integral[dev];
  }
}

int MTD415State::getIntegral(int dev){
  if (dev >= _devices){
    return -1;
  }
  return _integral[dev];
}

void MTD415State::updateDerivative(){
  for (int dev = 0; dev < _devices; dev++){
    _derivate[dev] = _connections.devices[dev]->getDerivative();
  }
}

void MTD415State::getDerivative(int * arr){
  for (int dev = 0; dev < _devices; dev++){
    arr[dev] = _derivate[dev];
  }
}

int MTD415State::getDerivative(int dev){
  if (dev >= _devices){
    return -1;
  }
  return _derivate[dev];
}

void MTD415State::setCriticalGain(int * arr){
  for (int dev = 0; dev < _devices; dev++){
    _connections.devices[dev]->setCriticalGain(arr[dev]);
  }
  this->updateCriticalGain();
}

void MTD415State::setCriticalPeriod(int * arr){
  for (int dev = 0; dev < _devices; dev++){
    _connections.devices[dev]->setCriticalPeriod(arr[dev]);
  }
  this->updateCriticalPeriod();
}

void MTD415State::setCyclingTime(int * arr){
  for (int dev = 0; dev < _devices; dev++){
    _connections.devices[dev]->setCyclingTime(arr[dev]);
  }
  this->updateCyclingTime();
}

void MTD415State::setProportional(int * arr){
  for (int dev = 0; dev < _devices; dev++){
    _connections.devices[dev]->setProportional(arr[dev]);
  }
  this->updateProportional();
}

void MTD415State::setIntegral(int * arr){
  for (int dev = 0; dev < _devices; dev++){
    _connections.devices[dev]->setIntegral(arr[dev]);
  }
  this->updateIntegral();
}

void MTD415State::setDerivative(int * arr){
  for (int dev = 0; dev < _devices; dev++){
    _connections.devices[dev]->setDerivative(arr[dev]);
  }
  this->updateDerivative();
}

// save settings

void MTD415State::saveSetup(int device){
  // not saving all devices because non-volatile memory on chip has finite
  // number of writes
  _connections.devices[device]->saveSetup();
}

// init

void MTD415State::initAll(){
  this->updateVersion();
  this->updateUUID();
  this->updateErrorRegister();
  this->updateTECCurrentLimit();
  this->updateTemperatureSetpoint();
  this->updateTemperatureWindow();
  this->updateTemperatureWindowDelay();
  this->updateCriticalGain();
  this->updateCriticalPeriod();
  this->updateCyclingTime();
  this->updateProportional();
  this->updateIntegral();
  this->updateDerivative(); 
}

void MTD415State::getEnabled(bool * arr){
  for (int dev = 0; dev < _devices; dev++){
    arr[dev] = _enabled[dev];
  }
}
