#include "Arduino.h"
#include "MTD415.h"

MTD415::MTD415(Stream *serial){
  _serial = (Stream *)serial;
  _response = "";
  _serial->setTimeout(500);
//  _serial->begin(115200);
}

String MTD415::_getResponse(){
  _response = _serial->readStringUntil('\n');
  if (_response == "unknown command"){
    return "";
  }
  return _response;
}

void MTD415::_writeCommand(String cmd, int value){
  delay(1);
  _serial->print(cmd);
  _serial->println(value);
  _response = this->_getResponse();
}

void MTD415::_writeCommand(String cmd){
  delay(1);
  _serial->print(cmd);
  _response = this->_getResponse();
}

int MTD415::_intReturnCMD(String cmd){

  delay(1);
  _serial->println(cmd);
  _response = this->_getResponse();
  if (_response.length() == 0){
    return -1;
  }
  else{
    return _response.toInt();
  }
}

String MTD415::_stringReturnCMD(String cmd){
  delay(1);
  _serial->println(cmd);
  _response = this->_getResponse();
  if (_response.length() == 0){
    return "";
  }
  else{
    return _response;
  }
}

// General commands

String MTD415::getVersion(){
  return this->_stringReturnCMD("m?");
}

String MTD415::getUUID(){
  return this->_stringReturnCMD("u?");
}

int MTD415::getErrorRegister(){
  return this->_intReturnCMD("E?");
}

void MTD415::resetErrorRegister(){
  this->_writeCommand("c");
}

//Temperature commands

int MTD415::getTemperature(){
  return this->_intReturnCMD("Te?");
}

int MTD415::getTemperatureSetpoint(){
  return this->_intReturnCMD("T?");
}

int MTD415::getTemperatureWindow(){
  return this->_intReturnCMD("W?");
}

int MTD415::getTemperatureWindowDelay(){
  return this->_intReturnCMD("d?");
}

//TEC commands

int MTD415::getTECCurrentLimit(){
  return this->_intReturnCMD("L?");
}

int MTD415::getTECCurrentActual(){
  return this->_intReturnCMD("A?");
}

int MTD415::getTECVoltage(){
  return this->_intReturnCMD("U?");
}

// Control loop

int MTD415::getCriticalGain(){
  return this->_intReturnCMD("G?");
}

int MTD415::getCriticalPeriod(){
  return this->_intReturnCMD("O?");
}

int MTD415::getCyclingTime(){
  return this->_intReturnCMD("C?");
}

int MTD415::getProportional(){
  return this->_intReturnCMD("P?");
}

int MTD415::getIntegral(){
  return this->_intReturnCMD("I?");
}

int MTD415::getDerivative(){
  return this->_intReturnCMD("D?");
}

void MTD415::setTemperatureSetpoint(int setpoint){
  this->_writeCommand("T", setpoint);
}

void MTD415::setTemperatureWindow(int window){
  this->_writeCommand("W", window);
}

void MTD415::setTemperatureWindowDelay(int delay){
  this->_writeCommand("d", delay);
}

void MTD415::setTECCurrentLimit(int limit){
  this->_writeCommand("L", limit);
}

void MTD415::setCriticalGain(int critical_gain){
  this->_writeCommand("G", critical_gain);
}

void MTD415::setCriticalPeriod(int critical_period){
  this->_writeCommand("O", critical_period);
}

void MTD415::setCyclingTime(int cycling_time){
  this->_writeCommand("C", cycling_time);
}

void MTD415::setProportional(int proportional){
  this->_writeCommand("P", proportional);
}

void MTD415::setIntegral(int integral){
  this->_writeCommand("I", integral);
}

void MTD415::setDerivative(int derivative){
  this->_writeCommand("D", derivative);
}

void MTD415::saveSetup(){
  _serial->println("M");
}
