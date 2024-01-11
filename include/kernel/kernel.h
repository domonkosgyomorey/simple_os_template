#ifndef KERNEL_H
#define KERNEL_H

#define KERNEL_START_MEMORY 0x1000

#define _init_driver_attrib __attribute__((section(".init_fun"))) 

typedef enum kernel_init_priority_t{
    KERNEL_INIT_SYSTEM_PRIORITY = 0,
    KERNEL_INIT_DRIVER_PRIORITY,
    KERNEL_INIT_COMMON_DRIVER_PRIORITY,
    KERNEL_INIT_PRIORITY_COUNT

}kernel_init_priority_t;

typedef void(*kernel_init_fun_t)();

typedef struct kernel_init_fun_s{
    kernel_init_fun_t init_fun;
    kernel_init_priority_t priority;
} kernel_init_fun_s ;

#define __init_driver__(init_fun_name, init_fun_ptr, _priority) \
    _init_driver_attrib kernel_init_fun_s init_fun_name##_s = (kernel_init_fun_s){.init_fun=init_fun_ptr, .priority=_priority};

void kernel_run_init_functions();

#endif // KERNEL_H