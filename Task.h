#ifndef Task_h
#define Task_h

#include <stdio.h>
#include <stdlib.h>
#include "Item.h"

typedef struct task_t {
    void (*f)(void*);
    void* args;
} * Task;


Item create_item(void* data);


#endif /* Item_h */
