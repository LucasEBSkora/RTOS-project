#include "Display.h"

Display::Display(uint8_t address, int scl_pin, int sda_pin) : driver{address, scl_pin, sda_pin}
{
  driver.init();
  driver.flipScreenVertically();
  driver.setFont(ArialMT_Plain_10);
}

void Display::run()
{
  TickType_t xLastWakeTime = xTaskGetTickCount();
  int t = 0;
  while(true) {
    driver.clear();

    driver.setFont(ArialMT_Plain_10);
    driver.setTextAlignment(TEXT_ALIGN_CENTER_BOTH);
    driver.drawString(64, 32, String(t));
    t = (t >= 60) ? t = 0 : t + 1;
    driver.display();
    vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(1000));
  }
}