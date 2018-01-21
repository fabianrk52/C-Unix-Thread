#ifndef Queue_h
#define Queue_h

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "Item.h"

typedef struct queue_t {
    Item head;
    Item tail;
    pthread_cond_t cond;
    pthread_mutex_t mutex;
    int count;
}*Queue;

Queue create_queue();
void enqueue(Queue queue, void* data);
void* dequeue(Queue queue);
int queue_is_empty(Queue queue);


#endif /* Queue_h */
