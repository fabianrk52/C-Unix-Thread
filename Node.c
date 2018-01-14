#include "Node.h"

Node create_node(void* data, Node next) {
    Node n = (Node)malloc(sizeof (struct node_t));
    n->data = (void*) data;
    n->next = NULL;
    return n;
}
