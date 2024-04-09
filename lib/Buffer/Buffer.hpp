#ifndef _BUFFER_HPP_
#define _BUFFER_HPP_
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

template <typename T>
class ThreadSafeBuffer
{
private:
  int capacity;
  T *buf;
  unsigned int readIndex;
  unsigned int writeIndex;
  SemaphoreHandle_t readSem;
  SemaphoreHandle_t writeSem;
  SemaphoreHandle_t readMutex;
  SemaphoreHandle_t writeMutex;

public:
  ThreadSafeBuffer(int capacity)
      : capacity{capacity}, buf{new T[capacity]}, readIndex{0}, writeIndex{0},
        readSem{xSemaphoreCreateCounting(capacity, 0)}, writeSem{xSemaphoreCreateCounting(capacity, capacity)},
        readMutex{xSemaphoreCreateMutex()}, writeMutex{xSemaphoreCreateMutex()} {};

  void write(T value)
  {
    xSemaphoreTake(writeSem, portMAX_DELAY);
    xSemaphoreTake(writeMutex, portMAX_DELAY);
    buf[writeIndex] = value;
    xSemaphoreGive(readSem);
    writeIndex = (writeIndex + 1) % capacity;
    xSemaphoreGive(writeMutex);
  }

  T read()
  {
    xSemaphoreTake(readSem, portMAX_DELAY);
    xSemaphoreTake(readMutex, portMAX_DELAY);
    T value = buf[readIndex];
    xSemaphoreGive(writeSem);
    readIndex = (readIndex + 1) % capacity;
    xSemaphoreGive(readMutex);
    return value;
  }
};
#endif