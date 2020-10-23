#include <Arduino.h>

// serial command string
String serial_command = "";

// relay pins
// order is [dev1, dev2, dev3]
int inputs_1[] = {11,10,9};
int inputs_2[] = {12,17,16};
int inputs_3[] = {15,14,13};
int active_device = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  // configuring outputs to control relays
  // and setting all switches in `open` state
  for (int i = 0; i < 3; i++){
    pinMode(inputs_1[i], OUTPUT);
    digitalWrite(inputs_1[i], LOW);
    pinMode(inputs_2[i], OUTPUT);
    digitalWrite(inputs_2[i], LOW);
    pinMode(inputs_3[i], OUTPUT);
    digitalWrite(inputs_3[i], LOW);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
}

void clear_all_switches(){
  /*
  Setting all switches in `open` state, ensuring no signal 
  is routed to the outputs
  */
  for (int i = 0; i < 3; i++){
    digitalWrite(inputs_1[i], LOW);
    digitalWrite(inputs_2[i], LOW);
    digitalWrite(inputs_3[i], LOW);    
  }
}

void select_device(int dev){
  /*
  Select signals from device `dev` to route through to the 
  output
  */
  if ((dev < 1 && dev > 3)){
    return;
  }
  clear_all_switches();
  digitalWrite(inputs_1[dev-1], HIGH);
  digitalWrite(inputs_2[dev-1], HIGH);
  digitalWrite(inputs_3[dev-1], HIGH);
  active_device = dev;
}

void handleSerial(){
  /*
  Define and handle serial commands
  */
  if (serial_command == "*IDN?"){
    // default identity function
    Serial.println("Cavity Signal Switcher V1.0");
  }
  else if (serial_command == "dev?"){
    // check current active device
    // return 0 for no device active
    Serial.println(active_device);
  }
  else if (serial_command.substring(0,3) == "dev"){
    // set device active, e.g. route intputs to outputs
    int device = serial_command.substring(4).toInt();
    select_device(device);
  }
  else if (serial_command == '?'){
    // print serial commands to serial
    Serial.println("Cavity Signal Switcher Commands:");
    Serial.println("*IDN?   : identitiy of device");
    Serial.println("dev?    : current selected device");
    Serial.println("dev x   : select device x, ranging from 1 to 3");
  }
  else{
    // invalid command catch and return
    Serial.print("invalid command : ");
    Serial.println(serial_command);
  }
}

void serialEvent(){
  while (Serial.available()){
    char c = (char)Serial.read();
    serial_command += c;
    if (c == '\n'){
      serial_command.trim();
      handleSerial();
      serial_command = "";
    }
  }
}