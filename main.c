//
//  main.c
//  unix2
//
//  Created by Fabian Roitman on 10/01/2018.
//  Copyright © 2018 Fabian. All rights reserved.
//

#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "List.h"
#include "poolManager.h"
#include "Task.h"
#include "montecarlo.h"
#include "taskFeeder.h"


int main(int argc, const char * argv[]) {
    
  int num_iterations;
    int num_threads;
    int num_tasks;
    int show_debug_messages;
    int iterations_per_task;
    int i;
    Task task;
    List tasks;
    TaskArgs task_args;
    Node temp;
    poolManager manager;
    TaskFeeder feeder;

    if (argc != 4) {
        perror("INSERT: NUM_ITERATIONS NUM_THREADS NUM_TASKS\n");
    }

    num_iterations = strtol(argv[1], NULL, 10);
    num_threads = atoi(argv[2]);
    num_tasks = atoi(argv[3]);
    iterations_per_task = num_iterations / num_tasks;


    printf("num_iterations = %d\nnum_threads = %d\nnum_tasks = %d\niterations_per_task = %d\n"
                ,num_iterations
                ,num_threads
                ,num_tasks
                ,iterations_per_task
            );
 
    int reminder_iterations = ceil(num_iterations % num_tasks);

    tasks = createList();
    manager = createPool(num_threads);
    printf("Thread pool manager was created with %d threads\n", num_threads);
    feeder = create_task_feeder(manager);
    printf("Task feeder was created\n");
    printf("a");
    for (i = 0; i < num_tasks; i++) {
        int iterations = iterations_per_task + (i == num_tasks - 1 ? reminder_iterations : 0);
        task_args = create_task_args(iterations);
        task = create_task(&monte_carlo_func, (void*) task_args);
        printf("Task #%d (id: %p) was created with %d iterations\n", i + 1, task, iterations);
        addtoList(tasks, (void*) task);
        feeder_load_task(feeder, task);
    }

    while (!all_tasks_finished(tasks)) {
        usleep(100);
    }


    manager_stop_all_threads(manager);
    printf("Stopped all threads\n");

    printf("PI estimation result is = %lf\n", estimate_pi(tasks));

    return 0;
}
