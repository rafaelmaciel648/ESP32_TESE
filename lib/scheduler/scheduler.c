#include "scheduler.h"

/* - Initialise data structures.
* - Configure interrupt that periodically calls Sched_Schedule().
*/
int Sched_Init(void){
    for(int x=0; x<20; x++)
        Tasks[x].func = 0;
};


/* Verifies if any task needs to be activated, and if so,
* increments by 1 the task's pending activation counter.
*/
void Sched_Schedule(void){
    for(int x=0; x<20; x++){
        if((Tasks[x].func) && (Tasks[x].delay)){
            Tasks[x].delay--;
            if(!Tasks[x].delay){
                /* Schedule Task */
                //Tasks[x].exec++;
                Tasks[x].delay = Tasks[x].period;
            }
        }
    }
};


/* Verifies if any task has an activation counter > 0,
* and if so, calls that task.
*/
// void Sched_Dispatch(void){
//     for(int x=0; x<20; x++){
//         if((Tasks[x].func) && (Tasks[x].exec)){
//             Tasks[x].exec--;
//             Tasks[x].func();            // Delete task if one-shot
//             if(!Tasks[x].period)
//                 Tasks[x].func = 0;
//         }
//     }
// };

int Sched_AddT(void (*f)(void), int d, int p){
    for(int x=0; x<20; x++){
        if(!Tasks[x].func){
            Tasks[x].period = p;
            Tasks[x].delay = d;
            // Tasks[x].exec = 0;
            Tasks[x].func = f;
            return x;
        }
    }
    return -1;
};