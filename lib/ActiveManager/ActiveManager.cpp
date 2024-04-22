#include "ActiveManager.h"

ActiveManager::ActiveManager() : active{false}, waitingTasks{0}, mutex{xSemaphoreCreateMutex()}, semaphore{xSemaphoreCreateBinary()}
{
}

void ActiveManager::setActive(bool active)
{
  this->active = active;
  if (!this->active || waitingTasks == 0)
    return;
  xSemaphoreTake(mutex, portMAX_DELAY);
  {
    for (int i = 0; i < waitingTasks; ++i)
      xSemaphoreGive(semaphore);
  }
  xSemaphoreGive(mutex);
}

void ActiveManager::checkActiveBlocking()
{
  if (active)
    return;
  xSemaphoreTake(mutex, portMAX_DELAY);
  {
    waitingTasks++;
  }
  xSemaphoreGive(mutex);
  xSemaphoreTake(semaphore, portMAX_DELAY);
}

bool ActiveManager::isActive()
{
  return active;
}