#include "SerialReceiverOtherESP.h"
#include <Wire.h>
#include "freertos/FreeRTOS.h"

SerialReceiverOtherESP::SerialReceiverOtherESP(uart_port_t port_num, int period_ms, int tx_pin, int rx_pin, ThreadSafeBuffer<Measurement> &buf, ActiveManager &activeManager)
    : port{port_num}, period_ticks{pdMS_TO_TICKS(period_ms)}, buffer{buf}, activeManager{activeManager}
{
  uart_config_t uart_config = {
      .baud_rate = 9600,
      .data_bits = UART_DATA_8_BITS,
      .parity = UART_PARITY_DISABLE,
      .stop_bits = UART_STOP_BITS_1,
      .flow_ctrl = UART_HW_FLOWCTRL_CTS_RTS,
  };

  if (uart_param_config(port, &uart_config) != ESP_OK)
  {
    printf("FAILED TO SETUP UART!\n");
  }
  uart_set_pin(port, tx_pin, rx_pin, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
  uart_driver_install(port, UART_FIFO_LEN + 1, 0, 0, NULL, 0);
}

void SerialReceiverOtherESP::run()
{
  TickType_t xLastWakeTime = xTaskGetTickCount();
  size_t available_bytes;
  uint8_t data[3];
  while (true)
  {
    uart_get_buffered_data_len(port, &available_bytes);
    if (available_bytes > 0)
    {

      int length = uart_read_bytes(port, data, 3, period_ticks / 10);
      printf("%u %u %u\n", data[0], data[1], data[2]);
      switch (data[0])
      {
      case 0:
        flagUserDetected(data[1]);
        break;
      case 1:
        addCO2Measurement(data[1], data[2]);
        break;
      }
    }
    vTaskDelayUntil(&xLastWakeTime, period_ticks);
  }
}

void SerialReceiverOtherESP::flagUserDetected(uint8_t val)
{
  activeManager.setActive(val);
  if (!val)
  {
    printf("no user detected!\n");
    return;
  }
  printf("user detected!\n");
}

void SerialReceiverOtherESP::addCO2Measurement(uint8_t high, uint8_t low)
{
  int Co2ppm = (((int)high) << 8) + low;
  Measurement m;
  m.type = measurementType::CO2;
  m.value.intValue = Co2ppm;
  buffer.write(m);
}