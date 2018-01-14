
#include "Task.h"

Task create_task(void (*f)(void*), void* args) {
    Task task = (Task) malloc(sizeof (struct task_t));
    task->f = f;
    task->args = args;
    return task;
}
