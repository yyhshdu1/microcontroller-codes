/**************************************************************************/
/*!
    @file     Adafruit_MMA8451.h
    @author   K. Townsend (Adafruit Industries)
    @license  BSD (see license.txt)

    This is an example for the Adafruit MMA8451 Accel breakout board
    ----> https://www.adafruit.com/products/2019

    Adafruit invests time and resources providing this open source code,
    please support Adafruit and open-source hardware by purchasing
    products from Adafruit!

    @section  HISTORY

    v1.0  - First release
*/
/**************************************************************************/

#include <Wire.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>

Adafruit_MMA8451 mma = Adafruit_MMA8451();

bool running = false;

void setup(void) {
  Serial.begin(9600);

  if (! mma.begin()) {
    while (1);
  }
  
  mma.setRange(MMA8451_RANGE_2_G);  
}

void HandleSerial() {
  while (Serial.available() > 0) {
    char cmd = Serial.read();
    switch (cmd) {
      case '?':
        Serial.println("ESP8266 Accelerometer");
        break;
      case 'R':
        running = true;
        break;
      case 'r':
        running = false;
        break;
      case 'm':
        mma.read();
        Serial.print(mma.x);Serial.print(",");
        Serial.print(mma.y);Serial.print(",");
        Serial.print(mma.z);Serial.println();
        break;
    }  
  }
}

void loop() {
  // Read the 'raw' data in 14-bit counts
  HandleSerial();
  if (running == true){
    mma.read();
    Serial.print(mma.x);Serial.print(",");
    Serial.print(mma.y);Serial.print(",");
    Serial.print(mma.z);Serial.println();
  }
}
