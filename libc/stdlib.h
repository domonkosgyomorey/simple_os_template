#ifndef STDLIB_H
#define STDLIB_H

#include "../x86_64/types.h"

void memncpy(void *source, void *dest, int nbytes);
void memset(void *dest, int val, int len);


#endif // STDLIB_H
