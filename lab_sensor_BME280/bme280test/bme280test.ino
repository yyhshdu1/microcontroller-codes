/*
 * Complete Project Details https://randomnerdtutorials.com
*/

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

const int CS[] = {2, 4, 6, 3, 5, 7};
//
//#define BME_SCK 13
//#define BME_MISO 12
//#define BME_MOSI 11
//#define BME_CS 10

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme; // I2C
//Adafruit_BME280 bme(BME_CS); // hardware SPI
//Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI

unsigned long delayTime;

void setup() {
  Serial.begin(9600);
  Serial.println(F("BME280 test"));

  bool status;
  Wire.begin(D3,D4);
  
  // default settings
  // (you can also pass in a Wire library object like &Wire2)
  status = bme.begin(0x76);  
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
  
  Serial.println("-- Default Test --");
  delayTime = 1000;

  Serial.println();
}


void loop() { 
  while (Serial.available()) {
    // read user input
    char c = (char)Serial.read();

    // decide what to do with it
    switch (c) {
      case '?':
        Serial.print("Sensor ready (B");
        Serial.println(").");
        break;
        
      case 'e':
        printValues();
        break;
  delay(delayTime);
    }
  }
}


void printValues() {
//  Serial.print("Temperature = ");
  Serial.print(bme.readTemperature());
  Serial.print(",");  // unit C
  
  // Convert temperature to Fahrenheit
  /*Serial.print("Temperature = ");
  Serial.print(1.8 * bme.readTemperature() + 32);
  Serial.println(" *F");*/
  
//  Serial.print("Pressure = ");
  Serial.print(bme.readPressure() / 100.0F);
  Serial.print(","); //unit hPa
 
  
//  Serial.print("Humidity = ");
  Serial.print(bme.readHumidity());
//  Serial.print(","); // unit %
  
  Serial.print('\n');
}
