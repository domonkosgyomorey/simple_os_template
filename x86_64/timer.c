#include "timer.h"
#include "isr.h"
#include "ports.h"
#include "../libc/stdlib.h"

u32 tick = 0;
tick_callback tick_callbacks[MAX_TICK_CALLBACK];
u8 tick_callbacks_count = 0;

s8 add_tick_callback(tick_callback tick_cb){
    if(tick_callbacks_count<MAX_TICK_CALLBACK){
        tick_callbacks[tick_callbacks_count++] = tick_cb;
        return 1;
    }else{
        return -1;
    }
}

static void timer_callback(registers_t regs) {
    tick++;
    for(int i = 0; i < tick_callbacks_count; ++i){
        tick_callbacks[i](tick);
    }
    (void)(regs);
}

void init_timer(u32 freq) {
    register_interrupt_handler(IRQ0, timer_callback);

    u32 divisor = CLOCK_HZ / freq;
    u8 low  = (u8)(divisor & 0xFF);
    u8 high = (u8)( (divisor >> 8) & 0xFF);
    outb(PIT_MODE_COMMAND, 0x36);              // tell the PIT which channel we're setting
    outb(PIT_CHANNEL0, low);
    outb(PIT_CHANNEL0, high);
}

