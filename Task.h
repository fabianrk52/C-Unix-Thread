#ifndef TASK_H
#define TASK_H

#include <stdlib.h>
#include "taskArgs.h"
#include "Node.h"
#include "List.h"

typedef struct task_t {
    void (*f)(void*);
    void* args;
} * Task;

Task create_task(void (*f)(void*), void* args);

#endif
