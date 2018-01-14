//
//  List.c
//  unix2
//
//  Created by Fabian Roitman on 11/01/2018.
//  Copyright © 2018 Fabian. All rights reserved.
//

#include "List.h"


List createList(){
    printf("list");
    List n_list=(List)malloc(sizeof(List));
    if(n_list==NULL)
        perror("create list memory allocation");
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
