#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include "SSD1306Wire.h"

class Display
{
public:
  Display(uint8_t address, int scl_pin, int sda_pin);
  void run();
private:
  SSD1306Wire driver;
};

#endif