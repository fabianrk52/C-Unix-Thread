#ifndef TASKARGS_H
#define TASKARGS_H

#include <stdlib.h>

typedef struct task_args_t {
    int dots_in_circle;
    int num_iterations;
    int finished;
} * TaskArgs;

TaskArgs create_task_args(int num_of_iterations);

#endif
