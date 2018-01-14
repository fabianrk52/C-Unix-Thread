#include "Item.h"


Item create_item(void* data){
    Item i = malloc (sizeof (struct item_t));
    i->data = (void*) data;
    i->next = NULL;
    return i;
}