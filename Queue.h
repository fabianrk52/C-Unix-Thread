#ifndef Queue_h
#define Queue_h

#include <stdio.h>
#include "Item.h"
#include <pthread.h>
#include <stdlib.h>

typedef struct queue_t {
    Item head;
    Item tail;
    pthread_cond_t cond;
    pthread_mutex_t mutex;
    int count;
}*Queue;

Queue create_queue(void);
void enqueue(Queue queue, void* data);
void* dequeue(Queue queue);
int EmptyQueue(Queue queue);


#endif /* Queue_h */
