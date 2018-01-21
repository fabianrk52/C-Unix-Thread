//
//  poolManager.c
//  unix2
//
//  Created by Fabian Roitman on 12/01/2018.
//  Copyright © 2018 Fabian. All rights reserved.
//

#include "poolManager.h"



poolManager createPool(int num_of_threads){  
     
    poolManager manager = (poolManager)malloc(sizeof(struct pool_manager_t));
    if(manager==NULL){
        perror("error: createPool()");
    }
    manager->tasks_queue=create_queue();
    printf("queue");
    manager->threads=createList();
    printf("crelist");
    for (int i = 0; i < num_of_threads; i++) {
        pthread_t* thread = (pthread_t*) malloc(sizeof (pthread_t));
        if (pthread_create(thread, NULL, thread_func, (void*) manager)){
            perror("pthread_create failed");
            exit(1);
        }
        addtoList(manager->threads, (void*) thread);
        printf("Thread #%d was created\n", i + 1);
    }
    return manager;
}


void* thread_func(void* args){
    poolManager manager = (poolManager) args;
    Task task;
    Queue tasks_queue = manager->tasks_queue;
    while (!0){
        task = (Task) dequeue(tasks_queue);
        printf("Thread %u took task %p\n", pthread_self(), task);
        task->f(task->args);
        printf("Thread %u finished task %p\n", pthread_self(), task);

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

