#include "ActiveManager.h"

ActiveManager::ActiveManager() : active{false}, listMutex{xSemaphoreCreateMutex()}
{
}

void ActiveManager::setActive(bool active)
{
  this->active = active;
  if (!this->active)
    return;
  xSemaphoreTake(listMutex, portMAX_DELAY);
  {
    for (TaskHandle_t task : waitingTasks)
    {
      xTaskNotify(task, 1, eSetBits);
    }
    waitingTasks.clear();
  }
  xSemaphoreGive(listMutex);
}

void ActiveManager::checkActiveBlocking()
{
  if (active)
    return;
  xSemaphoreTake(listMutex, portMAX_DELAY);
  {
    waitingTasks.push_back(xTaskGetCurrentTaskHandle());
    xTaskNotifyWait(0, ULONG_MAX, nullptr, portMAX_DELAY);
  }
  xSemaphoreGive(listMutex);
}

bool ActiveManager::isActive()
{
  return active;
}