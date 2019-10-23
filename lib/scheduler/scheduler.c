#include "scheduler.h"

#include <time.h>

/*
* Initialise empty data structures.
*/
int Sched_Init(void){
    for(int x=0; x<10; x++){
        Tasks[x].func = 0;
        Tasks[x].delay = 0;
        Tasks[x].period = 0;
        Tasks[x].nextExec = 0;
    }
    return 1;
};


/* 
* Routine to schedule all the tasks for next cycle.
*/
void Sched_Schedule(void){
    for(int x=0; x<10; x++){
        if( Tasks[x].func ){
            if(!Tasks[x].nextExec){                                 // if first schedule
                Tasks[x].nextExec = time(NULL) + Tasks[x].period;   // set time of next execution
            }
            else if(Tasks[x].nextExec){                             // if not first shedule
                Tasks[x].delay = Tasks[x].nextExec - time(NULL);    // update delay time
            }
        }
    }
};


/*
* Verifies the tasks to run this cycle. 
*/
void Sched_Dispatch(void){
    for(int x=0; x<10; x++){
        if( Tasks[x].func && ( Tasks[x].delay <= 0) ){              // time to execute
            Tasks[x].delay = Tasks[x].period;
            Tasks[x].nextExec = time(NULL) + Tasks[x].period;
            Tasks[x].func();
        }
    }
};

/*
* Add a read task to the scheduler.
* - void (*f)(void) - Read function;
* - int p - period in seconds;
*/
int Sched_AddT(void (*f)(void), int p){
    for(int x=0; x<10; x++){
        if(!Tasks[x].func){
            Tasks[x].period = p;
            Tasks[x].func = f;
            return x;
        }
    }
    return -1;
};

/*
* Function to clone Sched_Task_t struct. To save/read to/from de RTC memory before/after Depp Sleep.
*/
void copy_struct_to(Sched_Task_t *from_struct, Sched_Task_t *to_struct){
    for(int x=0; x<10; x++){
        to_struct[x] = from_struct[x];
    }
}