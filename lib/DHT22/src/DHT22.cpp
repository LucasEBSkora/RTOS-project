#include "DHT22.h"

DHT22::DHT22(int pin, int period_ms, ThreadSafeBuffer<Measurement> &buffer, ActiveManager &activeManager) : period_ticks{pdMS_TO_TICKS(period_ms)}, buf{buffer}, activeManager{activeManager}
{
  driver.setup(pin, DHTesp::DHT22);
  if (period_ms < driver.getMinimumSamplingPeriod())
  {
    throw "trying to sample temperature at a higher frequency than supported!";
  }
}

void DHT22::run()
{
  TickType_t xLastWakeTime = xTaskGetTickCount();
  while (true)
  {
    activeManager.checkActiveBlocking();
    float humidity = driver.getHumidity();
    float temperature = driver.getTemperature();
    Serial.println("humidity " + String(humidity));
    Serial.println("temperature " + String(temperature));

    buf.write({measurementType::HUMIDITY, humidity});
    buf.write({measurementType::TEMPERATURE, temperature});

    vTaskDelayUntil(&xLastWakeTime, period_ticks);
  }
}