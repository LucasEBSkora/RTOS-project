#include "DataMonitor.h"
#include <Wire.h>
#include "freertos/FreeRTOS.h"

DataMonitor::DataMonitor(ThreadSafeBuffer<Measurement> &buffer, int period_ms) : buf{buffer}, humidity{-1}, temperature{-1}, period_ticks{pdMS_TO_TICKS(period_ms)}
{
}

void DataMonitor::run()
{
  TickType_t xLastWakeTime = xTaskGetTickCount();
  while (true)
  {
    Measurement m = buf.read();
    switch (m.type)
    {
    case measurementType::TEMPERATURE:
      temperature = m.value.floatValue;
      printf("monitor: temperature = %.2f\n", m.value.floatValue);
      break;
    case measurementType::HUMIDITY:
      humidity = m.value.floatValue;
      printf("monitor: humidity = %.2f\n", m.value.floatValue);
      break;
    default:
      break;
    }
    vTaskDelayUntil(&xLastWakeTime, period_ticks);
  }
}

float DataMonitor::getTemperature() { return temperature; }
float DataMonitor::getHumidity() { return humidity; }
