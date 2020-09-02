#define VREF (3.292)         // ADC reference voltage (= power supply)
#define VINPUT (1.2)       // ADC input voltage from NiCd AA battery
#define ADCMAX (4095)        // maximum possible reading from ADC
#define BITVOLTS (VREF/ADCMAX)
#define NRSAMPLES (1000)

const int analogInPin = A1;  // Analog input is AIN1 (Teensy3 pin 14, next to LED)
const int LED1 = 13;         // output LED connected on Arduino digital pin 13

int x;
uint16_t arr_teensy_in1[NRSAMPLES];
uint16_t arr_A0_0[NRSAMPLES]

void setup() {
  pinMode(LED1, OUTPUT);      // enable digital output for turning on LED indicator
  // analogReference(EXTERNAL);  // set analog reference to internal ref
  analogReadRes(12);          // set ADC resolution to this many bits
  analogReadAveraging(1);    // average this many readings

  Serial.begin(115200);       // baud rate is ignored with Teensy USB ACM i/o
  digitalWrite(LED1, HIGH);   delay(1000);  // LED on for 1 second
  digitalWrite(LED1, LOW);    delay(3000);  // wait in case serial monitor still opening

  Serial.println("# Teensy ADC test start: ");
}


void loop() {
  handleSerial();
}

void handleSerial(){
  while (Serial.available() > 0){
    char cmd = Serial.read();
    switch (cmd) {
      case '1':
       get_teensy_in1();
//        Serial.print(arr_teensy_in1[0],2);
//        Serial.println();
        Serial.write((uint8_t*) arr_teensy_in1, sizeof(arr_teensy_in1));
//        Serial.println();
        break;
      case '2':
       
    }
  }
}

void get_teensy_in1(){
  for (int i = 0; i < NRSAMPLES; i++){
//    delayMicroseconds(1);
    arr_teensy_in1[i] = analogRead(analogInPin);
  }
}
