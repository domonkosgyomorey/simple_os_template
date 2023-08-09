#ifndef STDLIB_H
#define STDLIB_H

#include "../hdep/types.h"

void memncpy(void *source, void *dest, u32 nbytes);
void memset(void *dest, s32 val, u32 len);

#endif // STDLIB_H
