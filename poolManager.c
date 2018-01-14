//
//  poolManager.c
//  unix2
//
//  Created by Fabian Roitman on 12/01/2018.
//  Copyright © 2018 Fabian. All rights reserved.
//

#include "poolManager.h"
#include "Task.h"


poolManager createPool(int num_of_threads){
    poolManager manager = (poolManager)malloc(sizeof(struct thread_pool_manager_t));
    manager->tasks_queue=create_queue();
    manager->threads=createList();
    for(int i=num_of_threads;i>0;i--){
        pthread_t* thread=(pthread_t*)malloc(sizeof(pthread_t)); /*pthread_t = type for thread*/
        if(pthread_create(thread, NULL, thread_func, (void*)manager)){
            printf("pthread_create");
            exit(1);
        }
        addtoList(manager->threads, (void*)thread);
        printf("Thread #%d was created", i + 1);
    }
    return manager;
}


void* thread_func(void* args){
    poolManager manager = (poolManager) args;
    Task task;
    Queue tasks_queue = manager->tasks_queue;
    while (!0){
        task = (Task) dequeue(tasks_queue);
        printf("Thread %u took task %p", pthread_self(), task);
        task->f(task->args);
        printf("Thread %u finished task %p", pthread_self(), task);

    }
}
void manager_load_task(poolManager manager, void* task){
        enqueue(manager->tasks_queue, task);
}

void manager_stop_all_threads(poolManager manager){
    Node temp;
    pthread_t* thread;
    for (temp = manager->threads->prev; temp != NULL; temp = temp->next) {
        thread = (pthread_t*) temp->data;
        pthread_cancel(*thread);
    }
}

