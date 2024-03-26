#include <Wire.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "Display.h"

#define DISPLAY_ADDRESS 0x3c
#define DISPLAY_SCL 5
#define DISPLAY_SDA 4

Display* display;

void taskDisplay(void*) {
  display->run();
}

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println();

  display = new Display(DISPLAY_ADDRESS, DISPLAY_SCL, DISPLAY_SDA);
  xTaskCreate(taskDisplay, "Display", 10000, NULL, 1, NULL);
}

void loop() {
}