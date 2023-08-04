#ifndef STDLIB_H
#define STDLIB_H

#include "../x86_64/types.h"

void memncpy(int *source, int *dest, int nbytes);
void memset(int *dest, int val, int len);


#endif // STDLIB_H
