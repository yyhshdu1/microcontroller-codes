/*
Code for Digital isolator V1.1 with Arduino Nano
Intended to operate the YAG for CeNTREX, hooked up as follows:

CHANNELS  YAG
VIA       flashlamp output from control device
VIB       qswitch output from control device
VIC       flashlamp input
VID       qswitch input
ENA_C     either input for the switch controlling VIC to VOC
          or output signalling if switch is open (LOW) or closed (HIGH)
ENA_D     either input for the switch controlling VID to VOD
          or output signalling if switch is open (LOW) or closed (HIGH)

COMMANDS:
*IDN?             returns an identity string
qswitch (int)x    enables the qswitch for x shots, i.e. close switch VIC to VOC for x pulses on VIC
enable (char)x    enable channel x, where x is either C or D (i.e. close switch)
disable (char)x   disable channel x; where x is either C or D (i.e. open switch)
*/

// pin configuration
const int in_C = 2;
const int in_D = 3;
const int enable_C = 4;
const int out_C = 5;
const int enable_D = 6;
const int out_D = 7;

// counter configuration
int counter = 0;
int counter_max = 5;
bool counter_running = false;

// serial command string
String serial_command = "";

void _isr_final_D()
{
  // disable the switch for port D on a falling edge interrupt
  // temperarily making out_D an output pin to discharge the input of the 
  // isolator to ensure immidate switching of the out signal
  digitalWrite(enable_D,LOW);
  pinMode(out_D, OUTPUT);
  digitalWrite(out_D,LOW);
  pinMode(out_D, INPUT);
  detachInterrupt(digitalPinToInterrupt(in_D));
  counter_running = false;
}

void _isr_first_D(){
  if (counter == 1){
    counter = 0;
    digitalWrite(enable_D,HIGH);
    detachInterrupt(digitalPinToInterrupt(in_D));
    attachInterrupt(digitalPinToInterrupt(in_D), _isr_routine_D, RISING);
  }
  else{
    counter++;
  }
}

void _isr_routine_D(){
  //  interrupt routine to let the qswitch through counter_max times
  counter++;
  if (counter == counter_max)
  {
    counter = 0;
    detachInterrupt(digitalPinToInterrupt(in_D));
    // falling edge interrupt to disable the switch after the last pulse
    // to let through
    attachInterrupt(digitalPinToInterrupt(in_D), _isr_final_D, FALLING);
  }
}

void setup() {
  Serial.begin(9600);

  // pin configuration
  pinMode(in_C, INPUT);
  pinMode(in_D, INPUT);
  pinMode(enable_C, INPUT);
  pinMode(enable_D, INPUT);
  pinMode(out_C, INPUT);
  pinMode(out_D, INPUT);
}

void printCounterRunning(){
  Serial.print("invald : qswitch counter running : ");
  Serial.print(counter);
  Serial.print(" out of ");
  Serial.println(counter_max);
}

void handleSerial(){
  /*
  Handling serial commands, currently support:
  *IDN?             returns an identity string
  qswitch (int)x    enables the qswitch for x shots, i.e. close switch VIC to VOC for x pulses on VIC
  enable (char)x    enable channel x, where x is either C or D (i.e. close switch)
  disable (char)x   disable channel x; where x is either C or D (i.e. open switch)
  */
  if (serial_command == "*IDN?"){
    Serial.println("YAG Isolator V1.0");
  }
  else if (serial_command.substring(0,7) == "qswitch"){
    if (counter_running == false){
      counter_max = serial_command.substring(8).toInt();
      if (counter_max == 0)
      {
        Serial.print("invalid number of qswitches : ");
        Serial.println(counter_max);
        return;
      }
      counter_running = true;
      counter = 0;
      disable(enable_D);
      attachInterrupt(digitalPinToInterrupt(in_D), _isr_first_D, FALLING);
      Serial.print("qswitch ");
      Serial.println(counter_max);
    }
    else{
      printCounterRunning();
    }
  }
  else if (serial_command.substring(0,6) == "enable"){
    char c = serial_command.charAt(7);
    if (counter_running == true){
      printCounterRunning();
    }
    switch (c){
      case 'C':
        enable(enable_C, out_C);
        Serial.println("enable C");
        break;
      case 'D':
        enable(enable_D, out_D);
        Serial.println("enable D");
        break;
    } 
  }
  else if (serial_command.substring(0,7) == "disable"){
    char c = serial_command.charAt(8);
    if (counter_running == true){
      printCounterRunning();
    }
    switch (c){
      case 'C':
        disable(enable_C);
        break;
      case 'D':
        disable(enable_D);
        break;
    } 
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

void enable(const int en_pin, const int out_pin)
{
  // set an enable pin high, i.e. close switch from VI to VO
  // make sure we're not writing to the pin before enabling external control
  pinMode(out_pin, INPUT);

  // enable external control
  pinMode(en_pin, OUTPUT);
  digitalWrite(en_pin, HIGH);
}

void disable(const int en_pin)
{
  // disable external control, i.e. open switch from VI to VO
  pinMode(en_pin, OUTPUT);
  digitalWrite(en_pin, LOW);
}

void write_pin(const int en_pin, const int out_pin)
{
  // set output pin high, only possible for C or D
  // make sure external control is disabled before writing to the pin
  disable(en_pin);

  // write to the pin
  pinMode(out_pin, OUTPUT);
  digitalWrite(out_pin, HIGH);
}

void clear_pin(const int en_pin, const int out_pin)
{
  // clear an output pin, only possible for C or D
  // make sure external control is disabled before writing to the pin
  disable(en_pin);

  // write to the pin
  pinMode(out_pin, OUTPUT);
  digitalWrite(out_pin, LOW);
}

void loop() {
}
