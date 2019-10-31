#include "scheduler.h"

#include <time.h>

extern SchedTask tasks[10];

/*
* Initialise empty data structures.
*/
int Sched_Init(void){
    for(int i=0; i<10; i++){
        tasks[i].func = 0;
        tasks[i].delay = 0;
        tasks[i].period = 0;
        tasks[i].nextExec = 0;
    }
    return 1;
};


/* 
* Routine to schedule all the tasks for next cycle.
*/
void Sched_Schedule(void){
    for(int i=0; i<10; i++){
        if( tasks[i].func ){
            if(!tasks[i].nextExec){                                 // if first schedule
                tasks[i].nextExec = time(NULL) + tasks[i].period;   // set time of next execution
            }
            else if(tasks[i].nextExec){                             // if not first shedule
                tasks[i].delay = tasks[i].nextExec - time(NULL);    // update delay time
            }
        }
    }
};


/*
* Verifies the tasks to run this cycle. 
*/
void Sched_Dispatch(void){
    for(int i=0; i<10; i++){
        if( tasks[i].func && ( tasks[i].delay <= 0) ){              // time to execute
            tasks[i].delay = tasks[i].period;
            tasks[i].nextExec = time(NULL) + tasks[i].period;
            tasks[i].func();
        }
    }
};

/*
* Add a read task to the scheduler.
* - void (*f)(void) - Read function;
* - int p - period in seconds;
*/
int Sched_AddT(void (*f)(void), int p){
    for(int i=0; i<10; i++){
        if(!tasks[i].func){
            tasks[i].period = p;
            tasks[i].func = f;
            return i;
        }
    }
    return -1;
};