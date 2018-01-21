#ifndef TASKFEEDER_H
#define TASKFEEDER_H

#include <stdlib.h>
#include "poolManager.h"
#include "Task.h"

typedef struct taskfeeder {
     struct pool_manager_t *manager;
} * TaskFeeder;

TaskFeeder create_task_feeder(struct pool_manager_t *manager);
void feeder_load_task(TaskFeeder feeder, Task task);

#endif
