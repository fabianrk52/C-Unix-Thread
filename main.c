//
//  main.c
//  unix2
//
//  Created by Fabian Roitman on 10/01/2018.
//  Copyright © 2018 Fabian. All rights reserved.
//

#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "List.h"
#include "poolManager.h"
#include "Task.h"


typedef struct task_feeder_t {
    poolManager pool;
} * TaskFeeder;


TaskFeeder create_task_feeder(poolManager pool) {
    TaskFeeder feeder = (TaskFeeder) malloc(sizeof (struct task_feeder_t));
    feeder->pool = pool;
    return feeder;
}

int main(int argc, const char * argv[]) {
    
    int num_iterations,num_threads,num_tasks,interation_ptask,interation;
    Task task;
    List tasks;
    poolManager pool;
    TaskFeeder task_feeder;

    num_iterations=atoi(argv[0]);
    num_threads=atoi(argv[1]);
    num_tasks=atoi(argv[2]);
    num_iterations=num_iterations/num_tasks;
    
        
    tasks=createList();
    pool=createPool(num_threads);
    task_feeder=create_task_feeder(pool);
    
    for(int i=0;i<num_tasks;i++){
        interation = interation_ptask;
    }    
    
    
    printf("hello\n");
    
    
    
    
    
    
    return 0;
}
