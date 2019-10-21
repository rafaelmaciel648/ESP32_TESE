/*
* Struct with all read tasks
*/

typedef struct {
    int period;                     // period in seconds
    int delay;                      // seconds until next activation
    void (*func)(void);             // function pointer
//    int exec;                       // activation counter
} Sched_Task_t;

Sched_Task_t Tasks[20];


/* - Initialise data structures.
* - Configure interrupt that periodically calls Sched_Schedule().
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

int Sched_AddT(void (*f)(void), int d, int p);