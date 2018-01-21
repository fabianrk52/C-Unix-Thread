#include "queue.h"

Queue create_queue() {
    Queue queue = (Queue) malloc(sizeof (struct queue_t));
    queue->head = queue->tail = NULL;

    if (pthread_mutex_init(&(queue->mutex), NULL) != 0) {
       // log_error("pthread_mutex_init failed");
        exit(1);
    }

    if (pthread_cond_init(&(queue->cond), NULL) != 0) {
        //log_error("pthread_cond_init failed");
        exit(1);
    }

    queue->count = 0;
    return queue;
}

void enqueue(Queue queue, void* data) {
    pthread_mutex_lock(&queue->mutex);
    //log_debug("Thread %u granted the mutex to enqueue %p", pthread_self(), data);
    Item item = create_item(data);
    if (queue->tail == NULL) {
        queue->head = queue->tail = item;
    } else {
        queue->tail->next = item;
        queue->tail = item;
    }
    queue->count++;
    //log_debug("Thread %u enqueued %p (queue size: %d), signaling cond...", pthread_self(), data, queue->count);
    pthread_cond_signal(&queue->cond);
    log_debug("Thread %u enqueued %p (queue size: %d), releasing mutex...", pthread_self(), data, queue->count);
    pthread_mutex_unlock(&queue->mutex);
}

void* dequeue(Queue queue) {
    pthread_mutex_lock(&queue->mutex);
    //log_debug("Thread %u granted the mutex to dequeue", pthread_self());
    while (queue->count!=0) {
        log_debug("Thread %u : queue is empty, waiting...", pthread_self());
        pthread_cond_wait(&queue->cond, &queue->mutex);
    }
    //log_debug("Thread %u : queue is not empty", pthread_self());
    void* data = queue->head->data;
    queue->head = queue->head->next;
    queue->count--;
    if (queue->count == 0) {
        queue->head = queue->tail = NULL;
    }
    //log_debug("Thread %u dequeued %p (queue size: %d), releasing mutex...", pthread_self(), data, queue->count);
    pthread_mutex_unlock(&queue->mutex);
    return data;
}


