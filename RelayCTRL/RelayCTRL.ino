// Pin definitions
const int backingVacuum = 4;
const int beamsourceVacuum = 5;
const int relayCompressors = 12;

// input state definitions
int backingVacuumState = LOW;
int beamsourceVacuumState = LOW;

// relay state definitions
int relayCompressorsState = LOW;
  
void setup() {
  Serial.begin(9600);
  
  pinMode(backingVacuum, INPUT);
  pinMode(beamsourceVacuum, INPUT);
  pinMode(relayCompressors, OUTPUT);
}

void loop() {
  backingVacuumState = digitalRead(backingVacuum);
  beamsourceVacuumState = digitalRead(beamsourceVacuum);
  
  if (beamsourceVacuumState == HIGH) {
    digitalWrite(relayCompressors, HIGH);
    //Serial.print("Compressor interlock on\n");
  }
  else if (backingVacuumState == HIGH) {
    digitalWrite(relayCompressors, HIGH);
    Serial.print("Compressor interlock on\n");
  }
  else {
    digitalWrite(relayCompressors, LOW);
  }
  handleSerial();
}

void printInputState(){
  Serial.print(backingVacuumState);
  Serial.print(",");
  Serial.print(beamsourceVacuumState);
  Serial.print("\n");
}

void printRelayState(){
  Serial.print(digitalRead(relayCompressors));
  Serial.print("\n");
}

void handleSerial() {
  while (Serial.available() > 0) {
    char cmd = Serial.read();
    switch (cmd) {
      case 'I':
       printInputState();
       break;
      case 'R':
       printRelayState();
       break;
      case 'i':
       Serial.print("Relay CTRL Arduino\n");
       break;
      case '?':
       Serial.print("I = input states: backingVacuum, beamsourceVacuum; R = relay states: relayCompressors, i = identification string\n");
       break;
    }
  }
}
