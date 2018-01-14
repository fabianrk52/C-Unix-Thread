//
//  Queue.c
//  unix2
//
//  Created by Fabian Roitman on 12/01/2018.
//  Copyright © 2018 Fabian. All rights reserved.
//

#include "Queue.h"
#include <pthread.h>

Queue create_queue(void){
    Queue queue=(Queue)malloc(sizeof(struct queue_t));
    queue->head=NULL;
    queue->tail=NULL;
    if(pthread_mutex_init(&(queue->mutex),NULL))
       perror("pthread_mutex_init");
       exit(1);
    if(!(pthread_cond_init(&(queue->cond), NULL))){
        perror("pthread_cond_init");
        exit(1);
    }
    queue->count=0;
    return queue;
}

       
void enqueue(Queue queue, void* data){
    pthread_mutex_lock(&queue->mutex);
    printf("Thread %u granted the mutex to enqueue %p", pthread_self(), data);
    Item item = create_item(data);
    if (queue->tail == NULL) {
        queue->head = queue->tail = item;
    } else {
        queue->tail->next = item;
        queue->tail = item;
    }
    queue->count++;
    pritnf("Thread %u enqueued %p (queue size: %d), signaling cond...", pthread_self(), data, queue->count);
    pthread_cond_signal(&queue->cond);
    pritnf("Thread %u enqueued %p (queue size: %d), releasing mutex...", pthread_self(), data, queue->count);
    pthread_mutex_unlock(&queue->mutex);
}

void* dequeue(Queue queue){
    pthread_mutex_lock(&queue->mutex);
    printf("Thread %u granted the mutex to dequeue", pthread_self());
    while (queue_is_empty(queue)) {
        log_debug("Thread %u : queue is empty, waiting...", pthread_self());
        pthread_cond_wait(&queue->cond, &queue->mutex);
    }
    printf("Thread %u : queue is not empty", pthread_self());
    void* data = queue->head->data;
    queue->head = queue->head->next;
    queue->count--;
    if (queue->count == 0) {
        queue->head = queue->tail = NULL;
    }
    log_debug("Thread %u dequeued %p (queue size: %d), releasing mutex...", pthread_self(), data, queue->count);
    pthread_mutex_unlock(&queue->mutex);
    return data;
}

int EmptyQueue(Queue queue){
    return queue->count == 0;
}

