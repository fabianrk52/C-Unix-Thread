#ifndef List_h
#define List_h

#include <stdio.h>
#include <stdlib.h>
#include "Node.h"

typedef struct list_t{
    Node prev;
    Node next;
    int count;
}*List;


List createList(void);
void addtoList(List to_list, void* data);


#endif /* List_h */
