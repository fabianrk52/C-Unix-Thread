#include "List.h"


List createList(){
    List n_list=(List)malloc(sizeof(struct list_t));
    n_list->next=NULL;
    n_list->prev=NULL;
    n_list->count=0;
    return n_list;
}

void addtoList(List to_list, void* data){
    if(to_list==NULL){
        perror("List to add NULL");
        exit(1);
    }
    Node tmp = create_node(data,NULL);
    if(to_list->prev==NULL){
        to_list->next=tmp;
        to_list->prev=tmp;
    }
    else{
        to_list->prev->next=tmp;
        to_list->next=tmp;
    }
    to_list->count++;
}
