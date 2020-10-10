//#include <i2c_t3.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
//#include <Adafruit_SSD1306_teensy.h> // for use with i2c_t3.h
#include "symbols.h"
#include "MTD415.h"
#include "MTD415State.h"
#include "displayControl.h"
#include "SerialControl.h"
#include "physicalControl.h"
#include <Bounce2.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_SDA 18
#define OLED_SCL 19

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)

#define DISPLAY_CYCLE 3

// add sufficient enable lines and buttons if more devices are added!
int enable_lines[] = {2,9};
int enable_buttons[] = {4,5};

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// don't forget to enable the serial line!
MTD415 mtd415_1(&Serial1);
MTD415 mtd415_2(&Serial2);

MTD415State state(&mtd415_1, &mtd415_2);
DisplayControl display_ctrl(&display, &state);
PhysicalControl physical_ctrl(&state, &display_ctrl, enable_lines, enable_buttons, DISPLAY_CYCLE);
SerialControl serial_ctrl(&Serial, &state, &physical_ctrl, &display_ctrl);


String response;

void setup() {
  // setting up serial connections
  // Serial to PC
  Serial.begin(115200);
  // Serial to MTD415 number 1
  Serial1.begin(115200);
  Serial2.begin(115200);
  // Set up display
  Wire.setSDA(OLED_SDA);
  Wire.setSCL(OLED_SCL);
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }  // setup of physical control interfaces (buttons, enable lines)
  physical_ctrl.setup();
  // Display CeNTREX logo
  display_ctrl.displayCeNTREXLogo();
  delay(4000);

  // Initializing MTD415 state
  // reading variables from memory of MTD415
  state.initAll();
}

int temp[4];

void loop() {
  state.updateTemperature();
  state.updateTECCurrentActual();
  state.updateTECVoltage();
  state.updateErrorRegister();
  display_ctrl.updateDisplay();
  serial_ctrl.handleSerial();
  physical_ctrl.handlePhysical();
}
