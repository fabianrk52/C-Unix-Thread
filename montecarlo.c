#include "montecarlo.h"


double estimate_pi(List tasks) {
    Node t;
    Task task;
    TaskArgs task_args;
    double total_dots_in_circle = 0;
    double total_iterations = 0;
    for (t= tasks->prev; t!= NULL; t = t->next) {
        task = (Task) t->data;
        task_args = (TaskArgs) task->args;
        total_dots_in_circle += task_args->dots_in_circle;
        total_iterations += task_args->num_iterations;
    }
    return (total_dots_in_circle * 4) / total_iterations;
}


void monte_carlo_func(void* args) {
    double x, y, distance;
    int i = 0;
    TaskArgs task_args = (TaskArgs) args;
    srand(time(NULL));
    task_args->dots_in_circle = 0;
    for (i = 0; i < task_args->num_iterations; i++) {
        x = (double) rand() / (double) RAND_MAX;
        y = (double) rand() / (double) RAND_MAX;
        distance = pow(x - 0.5, 2) + pow(y - 0.5, 2);
        if (distance <= 0.25) {
            task_args->dots_in_circle += 1;
        }
    }
    task_args->finished = 1;
}