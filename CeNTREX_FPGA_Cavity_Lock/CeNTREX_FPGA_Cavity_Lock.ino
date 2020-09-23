#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "state.h"
#include "debounce.h"
#include "symbols.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define LOCK_BUTTON 2
#define SCAN_BUTTON 3
#define STATE_OUT1 4
#define STATE_OUT2 5
#define STATE_IN1 6
#define STATE_IN2 7

State cavity(STATE_IN1, STATE_IN2, STATE_OUT1, STATE_OUT2);
Button lockButton(LOCK_BUTTON, 50);
Button scanButton(SCAN_BUTTON, 50);

void setup() {
  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
}

void loop() {
  cavity.getState();
  if (cavity.scanState == HIGH) {
    displayScanning();
  }
  else if (cavity.lockState == HIGH && cavity.lockedState == LOW) {
    displayUnlocked();
  }
  else if (cavity.lockState == HIGH && cavity.lockedState == HIGH) {
    displayLocked();
  }
  else {
    displayLockOff();
  }
  if (lockButton.getStateChange() == HIGH) {
    cavity.toggleLock();
  }
  if (scanButton.getStateChange() == HIGH) {
    cavity.toggleScan();
  }
}

void displayLocked() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Laser Lock");
  display.setCursor(0, 25);
  display.println("State:");
  display.setCursor(0, 50);
  display.println("Locked");
  display.drawBitmap(128 - 40, 64 - 22, laser, 40, 22, SSD1306_WHITE);
  display.display();
}

void displayScanning() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Laser Lock");
  display.setCursor(0, 25);
  display.println("State:");
  display.setCursor(0, 50);
  display.println("Scan");
  display.drawBitmap(128 - 40, 64 - 22, ramp, 40, 22, SSD1306_WHITE);
  display.display();
}

void displayUnlocked() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Laser Lock");
  display.setCursor(0, 25);
  display.println("State:");
  display.setCursor(0, 50);
  display.println("Locking");
  display.drawBitmap(128 - 40, 64 - 22, unlocked, 40, 22, SSD1306_WHITE);
  display.display();
}

void displayLockOff() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Laser Lock");
  display.setCursor(0, 25);
  display.println("State:");
  display.setCursor(0, 50);
  display.println("Off");
  display.drawBitmap(128 - 30, 64 - 30, lock_off, 30, 30, SSD1306_WHITE);
  display.display();
}
