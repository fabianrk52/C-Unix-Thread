#include "taskArgs.h"

TaskArgs create_task_args(int num_of_iterations) {
    TaskArgs args = (TaskArgs) malloc(sizeof (struct task_args_t));
    args->dots_in_circle = 0;
    args->num_iterations = num_of_iterations;
    args->finished = 0;
    return args;
}

