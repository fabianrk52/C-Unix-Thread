#ifndef MONTECARLO_H
#define MONTECARLO_H

#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Task.h"
#include "Node.h"
#include "taskArgs.h"
#include <math.h>


double estimate_pi(List tasks);
void monte_carlo_func(void* args);




#endif
