/*
Code for the Arduino controller the shutter
Intended to operate the DIY HDD shutter for CeNTREX

COMMANDS:
*IDN?   returns an identity string
open    open the shutter
close   close the shutter
state   shutter state
*/

// pin configuration
const int shutter_ctrl_out  = 5;
const int shutter_state     = 6;

String serial_command = "";

void setup(){
    Serial.begin(9600);
    
    pinMode(shutter_ctrl_out, OUTPUT);
    pinMode(shutter_state, OUTPUT);
}

void handleSerial(){
  /*
  Handling serial commands, currently support:
  *IDN?     returns an identity string
  open      open the shutter
  close     close the shutter
  state     shutter state
  */
  if (serial_command == "*IDN?"){
    Serial.println("Shutter Controller V1.0");
  }
  else if (serial_command == "open")
  {
      open_shutter();
      Serial.println("open");
  }
  else if (serial_command == "close"){
      close_shutter();
      Serial.println("close");
  }
  else if (serial_command == "state"){
      Serial.println(digitalRead(shutter_ctrl_out));
  }
  else{
    Serial.print("invalid command : ");
    Serial.println(serial_command);
  }
}

void serialEvent() {
  while (Serial.available()) {
    char c = (char)Serial.read();
    serial_command += c;
    if (c == '\n'){
      serial_command.trim();
      handleSerial();
      serial_command = "";
    }
  }
}

void open_shutter(){
    digitalWrite(shutter_ctrl_out, HIGH);
    digitalWrite(shutter_state, HIGH);
}

void close_shutter(){
    digitalWrite(shutter_ctrl_out, LOW);
    digitalWrite(shutter_state, LOW);
}

void loop(){
}
