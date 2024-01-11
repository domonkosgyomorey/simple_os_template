#ifndef PROCESS_H
#define PROCESS_H

#include "registers.h"

#define MAX_PROCESS_NAME_LEN 32

typedef enum process_state {
    RUNNING,
    WAITING,
    BLOCKED,
    TERMINATED
} process_state;

typedef struct process_t{
    int pid;
    char name[MAX_PROCESS_NAME_LEN];
    registersX86_32_t regs;
    process_state state;
    int cpu_time;   // cpu quantum
} process_t;

// TODO: linked list
// TODO: quque for scheduler
// TODO: round robin scheduler
// TODO: time slices for scheduler

#endif // PROCESS_H