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
    Item item = create_item(data);
    if (queue->tail == NULL) {
        queue->head = queue->tail = item;
    } else {
        queue->tail->next = item;
        queue->tail = item;
    }
    queue->count++;
    pthread_cond_signal(&queue->cond);
    pthread_mutex_unlock(&queue->mutex);
}

void* dequeue(Queue queue) {
    pthread_mutex_lock(&queue->mutex);
    //log_debug("Thread %u granted the mutex to dequeue", pthread_self());
    while (queue_is_empty(queue)){
        pthread_cond_wait(&queue->cond, &queue->mutex);
    }
    void* data = queue->head->data;
    queue->head = queue->head->next;
    queue->count--;
    if (queue->count == 0) {
        queue->head = queue->tail = NULL;
    }
    pthread_mutex_unlock(&queue->mutex);
    return data;
}

int queue_is_empty(Queue queue) {
    return queue->count == 0;
}
