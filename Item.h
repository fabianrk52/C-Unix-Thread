#ifndef Item_h
#define Item_h

#include <stdio.h>
#include <stdlib.h>

typedef struct item_t {
    void* data;
    struct item_t* next;
}*Item;

Item create_item(void* data);


#endif
