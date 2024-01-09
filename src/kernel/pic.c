#include "kernel/pic.h"
#include "kernel/ports.h"

void pic_end_of_interrput(u8 irq, u8 irq_min){
    if(irq>=irq_min){
        outb(PIC_SLAVE_COMMAND, PIC_EOI);
    }
    outb(PIC_MASTER_COMMAND, PIC_EOI);
}

void pic_remap(u32 offset){

    // starts the initialization sequence (in cascade mode)
    outb(PIC_MASTER_COMMAND, PIC_ICW1_INIT | PIC_ICW1_ICW4);
    outb(PIC_SLAVE_COMMAND, PIC_ICW1_INIT | PIC_ICW1_ICW4);

    // ICW2: Master PIC vector offset
    outb(PIC_MASTER_DATA, offset);
    // ICW2: Slave PIC vector offset
    outb(PIC_SLAVE_DATA, offset+8);
    
    // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
    outb(PIC_MASTER_DATA, 0x04);
    outb(PIC_SLAVE_DATA, 0x02);
    
    // ICW4: have the PICs use 8086 mode (and not 8080 mode)
    outb(PIC_MASTER_DATA, PIC_ICW4_8086);
    outb(PIC_SLAVE_DATA, PIC_ICW4_8086);
    
    outb(PIC_MASTER_DATA, 0x0);
    outb(PIC_SLAVE_DATA, 0x0); 
}