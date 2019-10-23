/* SCHEDULER_H */

#ifndef SHEDULER_H
#define SHEDULER_H

#include <esp_attr.h>

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
} Sched_Task_t;

Sched_Task_t Tasks[10];             // consider maximum 10 read tasks


/* 
* - Initialise data structures.
*/
int Sched_Init(void);


/* Verifies if any task needs to be activated, and if so,
* increments by 1 the task's pending activation counter.
*/
void Sched_Schedule(void);


/* Verifies if any task has an activation counter > 0,
* and if so, calls that task.
*/
void Sched_Dispatch(void);

int Sched_AddT(void (*f)(void), int p);

void copy_struct_to(Sched_Task_t *from_struct, Sched_Task_t *to_struct);

#ifdef __cplusplus
}
#endif

#endif