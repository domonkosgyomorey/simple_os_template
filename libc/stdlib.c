#include "../x86_64/types.h"
#include "stdlib.h"

void memncpy(int *source, int *dest, int nbytes) {
    int i;
    for (i = 0; i < nbytes; i++) {
        *(dest + i) = *(source + i);
    }
}

void memset(int *dest, int val, int len) {
    int *temp = dest;
    for ( ; len != 0; len--) *temp++ = val;
}
