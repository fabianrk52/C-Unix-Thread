#ifndef Node_h
#define Node_h

#include <stdio.h>
#include <stdlib.h>

typedef struct node_t{
    void* data;
    struct node_t *next;
}*Node;

Node create_node(void* data, Node next);

#endif
