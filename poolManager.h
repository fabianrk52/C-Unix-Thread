#ifndef poolManager_h
#define poolManager_h

#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Queue.h"


typedef struct thread_pool_manager_t {
    Queue tasks_queue;
    List threads;
}*poolManager;

poolManager createPool(int num_of_threads);
void* thread_func(void* args);
void manager_load_task(poolManager manager, void* task);
void manager_stop_all_threads(poolManager manager);


#endif /* poolManager_h */
