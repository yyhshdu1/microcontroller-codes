const byte relayPin = 4;
const byte scopePin = 5;
const byte interruptPin = 3;
const int counter_max = 10;
int counter;
volatile byte state = LOW;

void setup() {
  pinMode(relayPin, OUTPUT);
  pinMode(scopePin, OUTPUT);
  digitalWrite(relayPin, LOW);
  digitalWrite(scopePin, LOW);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), relay, RISING);
}

void loop(){
}

void relay(){
  if (counter == (counter_max -1)){
    state = !state;
    delayMicroseconds(10000);
    delayMicroseconds(10000);
    delayMicroseconds(10000);
    digitalWrite(relayPin, state);
    digitalWrite(scopePin, state);
    counter = 0;
  }
  else{
    counter++;
  }
}
