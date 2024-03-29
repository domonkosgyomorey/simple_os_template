#ifndef PORTS_H
#define PORTS_H

#include "libc/types.h"

unsigned char inb (u16 port);
void outb (u16 port, u8 data);
unsigned short inw (u16 port);
void outw (u16 port, u16 data);

#endif