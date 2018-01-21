#include "taskFeeder.h"

TaskFeeder create_task_feeder(struct pool_manager_t *manager) {
    TaskFeeder feeder = (TaskFeeder) malloc(sizeof (struct taskfeeder));
    feeder->manager = manager;
    return feeder;
}

void feeder_load_task(TaskFeeder feeder, Task task) {
    manager_load_task(feeder->manager, task);
}

