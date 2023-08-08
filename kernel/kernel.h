#ifndef KERNEL_H
#define KERNEL_H

#define _init_driver_attrib __attribute__((section(".init_fun"))) 

typedef void(*kernel_init_fun_t)();

#endif // KERNEL_H