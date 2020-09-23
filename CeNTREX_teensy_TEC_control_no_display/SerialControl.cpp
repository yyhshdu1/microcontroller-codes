#include "Arduino.h"
#include "SerialControl.h"
#include "MTD415State.h"

SerialControl::SerialControl(Stream *serial, MTD415State *mtd415_state){
  _serial = (Stream *)serial;
  _mtd415_state = (MTD415State *)mtd415_state;
}

void SerialControl::printOptions(){
  _serial->println("MTD415 based temperature controller");
  _serial->println("Options:");
  _serial->println("m? : get version(s)");
  _serial->println("u? : get UUID");
  _serial->println("E? : get error(s)");
  _serial->println("Te? : get temperature(s)");
  _serial->println("T? : get temperature setpoint(s)");
  _serial->println("W? : get temperature window");
  _serial->println("d? : get temperature window delay");
  _serial->println("L? : get TEC current limit(s)");
  _serial->println("A? : get actual TEC current(s)");
  _serial->println("U? : get actual TEC voltage(s)");
  _serial->println("G? : get critical gain(s)");
  _serial->println("O? : get critical period(s)");
  _serial->println("C? : get cycling time(s)");
  _serial->println("P? : get proportional share(s)");
  _serial->println("I? : get integral share(s)");
  _serial->println("D? : get derivative share(s)");
  _serial->println("To change value use Tx! where x is the new value.");
  _serial->println("cx! : reset error register of device x");
}

void SerialControl::_sendArray(int * arr, int len){
  for (int i = 0; i < len; i++){
    _serial->print(arr[i]);
    if (i < len -1){
      _serial->print(",");
    }
  }
  _serial->print("\n");
}

void SerialControl::_sendArray(String * arr, int len){
  for (int i = 0; i < len; i++){
    _serial->print(arr[i]);
    if (i < len -1){
      _serial->print(",");
    }
  }
  _serial->print("\n");
}

void SerialControl::_handleQuery(){
    if (_response == "Te?"){
      _mtd415_state->getTemperature(_iarray);
      this->_sendArray(_iarray, _mtd415_state->devices);
    }
    else if (_response == "m?"){
      _mtd415_state->getVersion(_sarray);
      this->_sendArray(_sarray, _mtd415_state->devices);
    }
    else if (_response == "u?"){
      _mtd415_state->getUUID(_sarray);
      this->_sendArray(_sarray, _mtd415_state->devices);
    }
    else if (_response == "E?"){
      _mtd415_state->getErrorRegister(_iarray);
      this->_sendArray(_iarray, _mtd415_state->devices);
    }
    else if (_response == "T?"){
      _mtd415_state->getTemperatureSetpoint(_iarray);
      this->_sendArray(_iarray, _mtd415_state->devices);
    }
    else if (_response == "W?"){
      _mtd415_state->getTemperatureWindow(_iarray);
      this->_sendArray(_iarray, _mtd415_state->devices);
    }
    else if (_response == "d?"){
      _mtd415_state->getTemperatureWindowDelay(_iarray);
      this->_sendArray(_iarray, _mtd415_state->devices);
    }
    else if (_response == "L?"){
      _mtd415_state->getTECCurrentLimit(_iarray);
      this->_sendArray(_iarray, _mtd415_state->devices);
    }
    else if (_response == "A?"){
      _mtd415_state->getTECCurrentActual(_iarray);
      this->_sendArray(_iarray, _mtd415_state->devices);
    }
    else if (_response == "U?"){
      _mtd415_state->getTECVoltage(_iarray);
      this->_sendArray(_iarray, _mtd415_state->devices);
    }
    else if (_response == "G?"){
      _mtd415_state->getCriticalGain(_iarray);
      this->_sendArray(_iarray, _mtd415_state->devices);
    }
    else if (_response == "O?"){
      _mtd415_state->getCriticalPeriod(_iarray);
      this->_sendArray(_iarray, _mtd415_state->devices);
    }
    else if (_response == "C?"){
      _mtd415_state->getCyclingTime(_iarray);
      this->_sendArray(_iarray, _mtd415_state->devices);
    }
    else if (_response == "P?"){
      _mtd415_state->getProportional(_iarray);
      this->_sendArray(_iarray, _mtd415_state->devices);
    }
    else if (_response == "I?"){
      _mtd415_state->getIntegral(_iarray);
      this->_sendArray(_iarray, _mtd415_state->devices);
    }
    else if (_response == "D?"){
      _mtd415_state->getDerivative(_iarray);
      this->_sendArray(_iarray, _mtd415_state->devices);
    }
    else if (_response == "?"){
      this->printOptions();
    }
    else{
      _serial->println("invalid read command");
    }
}

void SerialControl::_stringToArray(String str, int * arr)
{
  int devices = _mtd415_state->devices;
  int comma_index_1, comma_index_2;

  if (devices == 1){
    arr[0] = str.toInt();
  }
  else {
    for (int i = 0; i < devices; i++){
      if (i == 0){
        comma_index_1 = str.indexOf(',');
        arr[i] = str.substring(0,comma_index_1).toInt();
      }
      else if (i < devices - 1){
        comma_index_2 = str.indexOf(',', comma_index_1+1);
        arr[i] = str.substring(comma_index_1 + 1, comma_index_2).toInt();
        comma_index_1 = comma_index_2;
      }
      else{
        if (devices == 2){
          arr[i] = str.substring(comma_index_1 + 1).toInt();
        }
        else{
          arr[i] = str.substring(comma_index_2 + 1).toInt();
        }
      }
    }
  }
}

void SerialControl::_handleWrite(){
  char cmd = _response[0];
  int len = _response.length();
  switch(cmd){
    case 'L':
      this->_stringToArray(_response.substring(1,len-1), _iarray);
      _mtd415_state->setTECCurrentLimit(_iarray);
      break;
    case 'T':
      this->_stringToArray(_response.substring(1,len-1), _iarray);
      _mtd415_state->setTemperatureSetpoint(_iarray);
      break;
    case 'G':
      this->_stringToArray(_response.substring(1,len-1), _iarray);
      _mtd415_state->setCriticalGain(_iarray);
      break;
    case 'O':
      this->_stringToArray(_response.substring(1,len-1), _iarray);
      _mtd415_state->setCriticalPeriod(_iarray);
      break;
    case 'C':
      this->_stringToArray(_response.substring(1,len-1), _iarray);
      _mtd415_state->setCyclingTime(_iarray);
      break;
    case 'P':
      this->_stringToArray(_response.substring(1,len-1), _iarray);
      _mtd415_state->setProportional(_iarray);
      break;
    case 'I':
      this->_stringToArray(_response.substring(1,len-1), _iarray);
      _mtd415_state->setIntegral(_iarray);
      break;
    case 'D':
      this->_stringToArray(_response.substring(1,len-1), _iarray);
      _mtd415_state->setDerivative(_iarray);
      break;
    case 'c':
      _mtd415_state->resetErrorRegister(_response.substring(1,len-1).toInt());
      break;
    case 'W':
      this->_stringToArray(_response.substring(1,len-1), _iarray);
      _mtd415_state->setTemperatureWindow(_iarray);
      break;
    case 'd':
      this->_stringToArray(_response.substring(1,len-1), _iarray);
      _mtd415_state->setTemperatureWindowDelay(_iarray);
      break;
    case 'M':
      _mtd415_state->saveSetup(_response.substring(1,len-1).toInt());
      break;
    default:
      _serial->println("invalid write command");
  }
}

void SerialControl::handleSerial(){
  if (Serial.available() > 0){
    _response = Serial.readStringUntil('\n');
    int len = _response.length();
    if (_response[len-1] == '?'){
      this->_handleQuery();
    }
    else if (_response[len-1] == '!'){
      this->_handleWrite();
    }
    else{
      _serial->println("invalid command");
    }
  }
}
