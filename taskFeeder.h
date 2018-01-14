#ifndef TASKFEEDER_H
#define TASKFEEDER_H

#include <stdlib.h>
#include "poolManager.h"
#include "task.h"

typedef struct taskfeeder {
    poolManager manager;
} * TaskFeeder;

TaskFeeder create_task_feeder(poolManager manager);
void feeder_load_task(TaskFeeder feeder, Task task);

#endif
