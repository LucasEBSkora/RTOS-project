#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include "freertos/FreeRTOS.h"
#include "SSD1306Wire.h"
#include "DataMonitor.h"
#include "ActiveManager.h"

class Display
{
public:
  Display(uint8_t address, int scl_pin, int sda_pin, int period_ms, DataMonitor &monitor, ActiveManager &activeManager);
  void run();

private:
  SSD1306Wire driver;
  TickType_t period_ticks;
  DataMonitor &monitor;
  ActiveManager &activeManager;
};

#endif