#include "libc/types.h"
#include "libc/stdlib.h"

void memncpy(void *source, void *dest, u32 nbytes) {
    char* csource = (char*)source;
    char* cdest = (char*)dest;
    
    for (u32 i = 0; i < nbytes; i++) {
        *(cdest + i) = *(csource + i);
    }
}

void memset(void *dest, s32 val, u32 len) {
    char *temp = dest;
    for ( ; len != 0; len--) *temp++ = val;
}