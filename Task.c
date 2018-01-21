#include "Task.h"

Task create_task(void (*f)(void*), void* args) {
    Task task = (Task) malloc(sizeof (struct task_t));
    task->f = f;
    task->args = args;
    return task;
}


int all_tasks_finished(List tasks) {
    Node temp;
    Task task;
    TaskArgs task_args;
    for (temp = tasks->prev; temp != NULL; temp = temp->next) {
        task = (Task) temp->data;
        task_args = (TaskArgs) task->args;
        if (!task_args->finished) {
            return 0;
        }
    }
    return 1;
}
