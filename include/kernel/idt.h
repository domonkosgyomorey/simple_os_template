#ifndef IDT_H
#define IDT_H

#include "libc/types.h"

/* Segment selectors */
#define KERNEL_CS 0x08

typedef struct {
    u16 low_offset;
    u16 sel;
    u8 always0;
    u8 flags; 
    u16 high_offset;
} __attribute__((packed)) idt_gate_t ;

/* A pointer to the array of interrupt handlers.
 * Assembly instruction 'lidt' will read it */
typedef struct {
    u16 limit;
    u32 base;
} __attribute__((packed)) idt_register_t;

#define IDT_ENTRIES 256

void set_idt_gate(int n, u32 handler);
void set_idt();

#endif
