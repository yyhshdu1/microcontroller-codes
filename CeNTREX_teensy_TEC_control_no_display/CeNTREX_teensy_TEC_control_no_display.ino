#include "symbols.h"
#include "MTD415.h"
#include "MTD415State.h"
#include "SerialControl.h"

MTD415 mtd415_1(&Serial2);
MTD415State state(&mtd415_1);
SerialControl serial_ctrl(&Serial, &state);

String response;

void setup() {
  // setting up serial connections
  // Serial to PC
  Serial.begin(115200);
  
  // Serial to MTD415 number 1
  Serial2.begin(115200);
  // Initializing MTD415 state
  // reading variables from memory of MTD415
  state.initAll();
  delay(1000);
  Serial.println("MTD415 based temperature controller");
}

int temp[4];

void loop() {
  state.updateTemperature();
  state.updateTECCurrentActual();
  state.updateTECVoltage();
  state.updateErrorRegister();
  serial_ctrl.handleSerial();
}
