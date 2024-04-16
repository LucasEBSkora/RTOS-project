#ifndef __DATA_MONITOR_H__
#define __DATA_MONITOR_H__

#include "Buffer.hpp"
#include "Measurement.hpp"

class DataMonitor
{
public:
  DataMonitor(ThreadSafeBuffer<Measurement> &buffer, int period_ms);
  void run();
  float getHumidity();
  float getTemperature();
  int getCO2ppm();

private:
  ThreadSafeBuffer<Measurement> &buf;
  float humidity;
  float temperature;
  int CO2ppm;
  TickType_t period_ticks;
};
#endif