/* SCHEDULER_H */

#ifndef SHEDULER_H
#define SHEDULER_H

#include <Arduino.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
* Struct with all read tasks
*/

typedef struct {
    int period;                     // period in seconds
    int delay;                      // seconds until next activation
    unsigned long nextExec;         // UNIX time of next activation
    void (*func)(void);             // function pointer
} SchedTask;


/*
* Initialise empty data structures.
*/
int Sched_Init(void);


/* 
* Routine to schedule all the tasks for next cycle.
*/
void Sched_Schedule(void);


/*
* Verifies the tasks to run this cycle. 
*/
void Sched_Dispatch(void);


/*
* Add a read task to the scheduler.
* - void (*f)(void) - Read function;
* - int p - period in seconds;
*/
int Sched_AddT(void (*f)(void), int p);


#ifdef __cplusplus
}
#endif

#endif