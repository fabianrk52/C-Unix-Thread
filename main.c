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


typedef struct task_feeder_t {
    poolManager pool;
} * TaskFeeder;


TaskFeeder create_task_feeder(poolManager pool) {
    TaskFeeder feeder = (TaskFeeder) malloc(sizeof (struct task_feeder_t));
    feeder->pool = pool;
    return feeder;
}

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
    TreadPoolManager manager;
    TaskFeeder feeder;

    if (argc != 5) {
        log_error("Usage: ./main NUM_ITERATIONS NUM_THREADS NUM_TASKS SHOW_DEBUG_MESSAGES");
        exit(1);
    }

    num_iterations = strtol(argv[1], NULL, 10);
    num_threads = atoi(argv[2]);
    num_tasks = atoi(argv[3]);
    show_debug_messages = atoi(argv[4]);
    iterations_per_task = num_iterations / num_tasks;

    log_init(show_debug_messages);

    log_debug("num_iterations = %d", num_iterations);
    log_debug("num_threads = %d", num_threads);
    log_debug("num_tasks = %d", num_tasks);
    log_debug("iterations_per_task = %d", iterations_per_task);

    int reminder_iterations = num_iterations % num_tasks;
    if (reminder_iterations != 0) {
        log_info("Last task will be %d iterations because %d %% %d = %d"
                , iterations_per_task + reminder_iterations
                , num_iterations
                , num_tasks
                , reminder_iterations);
    }

    tasks = create_list();
    manager = create_pool_manager(num_threads);
    log_debug("Thread pool manager was created with %d threads", num_threads);
    feeder = create_task_feeder(manager);
    log_debug("Task feeder was created");

    for (i = 0; i < num_tasks; i++) {
        int iterations = iterations_per_task + (i == num_tasks - 1 ? reminder_iterations : 0);
        task_args = create_task_args(iterations);
        task = create_task(&monte_carlo_func, (void*) task_args);
        log_debug("Task #%d (id: %p) was created with %d iterations", i + 1, task, iterations);
        add_to_list(tasks, (void*) task);
        feeder_load_task(feeder, task);
    }

    while (!all_tasks_finished(tasks)) {
        usleep(100);
    }


    manager_stop_all_threads(manager);
    log_debug("Stopped all threads");

    log_info("PI estimation result is = %lf", estimate_pi(tasks));

    return 0;
}
