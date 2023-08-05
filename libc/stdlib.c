#include "../hdep/types.h"
#include "stdlib.h"

void memncpy(void *source, void *dest, int nbytes) {
    char* csource = (char*)source;
    char* cdest = (char*)dest;
    
    for (int i = 0; i < nbytes; i++) {
        *(cdest + i) = *(csource + i);
    }
}

void memset(void *dest, int val, int len) {
    char *temp = dest;
    for ( ; len != 0; len--) *temp++ = val;
}
