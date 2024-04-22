#ifndef __ACTIVE_MANAGER_H__
#define __ACTIVE_MANAGER_H__

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#include <vector>
class ActiveManager
{
public:
  ActiveManager();
  void setActive(bool active);
  void checkActiveBlocking();
  bool isActive();

private:
  bool active;
  int waitingTasks;
  SemaphoreHandle_t mutex;
  SemaphoreHandle_t semaphore;
};

#endif