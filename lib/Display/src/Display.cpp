#include "Display.h"

Display::Display(uint8_t address, int scl_pin, int sda_pin, int period_ms, DataMonitor &monitor) : driver{address, scl_pin, sda_pin}, period_ticks{pdMS_TO_TICKS(period_ms)}, monitor{monitor}
{
  driver.init();
  driver.clear();
  driver.flipScreenVertically();
  driver.setFont(ArialMT_Plain_10);
  driver.display();

}

void Display::run()
{
  TickType_t xLastWakeTime = xTaskGetTickCount();

  while (true)
  {
    driver.clear();

    float temperature = monitor.getTemperature();
    float humidity = monitor.getHumidity();

    String text = String("Temperature: ") + temperature  + "\nHumidity: " + humidity;

    driver.setTextAlignment(TEXT_ALIGN_CENTER_BOTH);
    driver.drawString(64, 32, text);
    driver.display();
    vTaskDelayUntil(&xLastWakeTime, period_ticks);
  }
}