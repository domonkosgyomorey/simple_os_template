#ifndef REGISTERS_H
#define REGISTERS_H

typedef struct registersX86_32_t {
    unsigned int eax, ebx, ecx, edx;
    unsigned int esi, edi;
    unsigned int ebp, esp;
    unsigned int eip;
    unsigned int eflags;
    unsigned int cs, ds, es, fs, gs;
    unsigned int ss; // Stack segment register
} registersX86_32_t;

#endif // REGISTERS_H