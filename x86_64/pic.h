#ifndef PIC_H
#define PIC_H

#include "types.h"
#include "ports.h"

#define PIC_MASTER_COMMAND      0x20
#define PIC_MASTER_DATA         0x21
#define PIC_SLAVE_COMMAND       0xA0
#define PIC_SLAVE_DATA          0xA1
#define PIC_SLAVE_OFFSET        8

/* reinitialize the PIC controllers, giving them specified vector offsets
   rather than 8h and 70h, as configured by default */
 
#define PIC_ICW1_ICW4	            0x01		/* Indicates that ICW4 will be present */
#define PIC_ICW1_SINGLE	            0x02		/* Single (cascade) mode */
#define PIC_ICW1_INTERVAL4	        0x04		/* Call address interval 4 (8) */
#define PIC_ICW1_LEVEL	            0x08		/* Level triggered (edge) mode */
#define PIC_ICW1_INIT	            0x10		/* Initialization - required! */
 
#define PIC_ICW4_8086	            0x01		/* 8086/88 (MCS-80/85) mode */
#define PIC_ICW4_AUTO	            0x02		/* Auto (normal) EOI */
#define PIC_ICW4_BUF_SLAVE	        0x08		/* Buffered mode/slave */
#define PIC_ICW4_BUF_MASTER	        0x0C		/* Buffered mode/master */
#define PIC_ICW4_SFNM	            0x10		/* Special fully nested (not) */

#define PIC_EOI                 0x20

void pic_end_of_interrput(u8 irq, u8 irq_min);
void pic_remap(u32 offset);

#endif // PIC_H