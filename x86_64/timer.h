#ifndef TIMER_H
#define TIMER_H

#include "types.h"

#define MAX_TICK_CALLBACK   32

#define PIT_CHANNEL0        0x40
#define PIT_CHANNEL1        0x41
#define PIT_CHANNEL2        0x42
#define PIT_MODE_COMMAND    0x43

#define CLOCK_HZ            1193180

typedef void (*tick_callback)(u32 tick);
void init_timer(u32 freq);
s8 add_tick_callback(tick_callback tick_cb);

#endif
