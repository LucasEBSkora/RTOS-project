#include <Wire.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "Display.h"
#include "DHT22.h"
#include "DataMonitor.h"

#include "Buffer.hpp"
#include "Measurement.hpp"

#define DISPLAY_ADDRESS 0x3c
#define DISPLAY_SCL 5
#define DISPLAY_SDA 4

#define DHT22_PIN 15

ThreadSafeBuffer<Measurement> buffer{20};
DataMonitor monitor{buffer, 1000};

void taskDisplay(void *)
{
  Display display{DISPLAY_ADDRESS, DISPLAY_SCL, DISPLAY_SDA, 1000, monitor};
  display.run();
}

void taskTemperatureHumiditySensor(void *)
{
  DHT22 temperatureHumiditySensor{DHT22_PIN, 5000, buffer};
  temperatureHumiditySensor.run();
}

void taskDataMonitor(void *)
{
  monitor.run();
}

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println();

  xTaskCreate(taskDataMonitor, "monitor", 10000, NULL, 9, NULL);
  xTaskCreate(taskDisplay, "Display", 10000, NULL, 1, NULL);
  xTaskCreate(taskTemperatureHumiditySensor, "DHT22", 10000, NULL, 1, NULL);
}

void loop()
{
}