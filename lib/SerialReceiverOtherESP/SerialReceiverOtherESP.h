#ifndef __SERIAL_RECEIVER_OTHER_ESP_H__
#define __SERIAL_RECEIVER_OTHER_ESP_H__

#include "freertos/FreeRTOS.h"
#include "driver/uart.h"
#include "Buffer.hpp"
#include "Measurement.hpp"
#include "ActiveManager.h"

class SerialReceiverOtherESP
{
public:
  SerialReceiverOtherESP(uart_port_t port_num, int period_ms, int tx_pin, int rx_pin, ThreadSafeBuffer<Measurement> &buf, ActiveManager &activeManager);
  void run();

private:
  bool flagUserDetected(uint8_t val);
  void addCO2Measurement(uint8_t high, uint8_t low);
  uart_port_t port;
  TickType_t period_ticks;
  ThreadSafeBuffer<Measurement> &buffer;
  ActiveManager &activeManager;
};

#endif