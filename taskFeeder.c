#include "taskFeeder.h"

TaskFeeder create_task_feeder(poolManager manager) {
    TaskFeeder feeder = (TaskFeeder) malloc(sizeof (struct taskfeeder));
    feeder->manager = manager;
    return feeder;
}

void feeder_load_task(TaskFeeder feeder, Task task) {
    manager_load_task(feeder->manager, task);
}

