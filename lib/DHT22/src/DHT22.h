#ifndef __DHT22_H__
#define __DHT22_H__

#include "DHTesp.h"
#include "freertos/FreeRTOS.h"

#include "Buffer.hpp"
#include "Measurement.hpp"
#include "ActiveManager.h"

class DHT22
{
public:
  DHT22(int pin, int period_ms, ThreadSafeBuffer<Measurement> &buffer, ActiveManager &activeManager);
  void run();

private:
  DHTesp driver;
  TickType_t period_ticks;
  ThreadSafeBuffer<Measurement> &buf;
  ActiveManager &activeManager;
};
#endif