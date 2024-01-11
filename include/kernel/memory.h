#ifndef MEMORY_H
#define MEMORY_H

#include "libc/bool.h"

#define MIN_BLOCK_SIZE 16

#define NULL 0x0

typedef struct memory_block_t {
    struct memory_block_t* left;
    struct memory_block_t* right;
    bool free;
    unsigned int size;
} memory_block_t;

void initialize_memory(void* memory, unsigned int memory_size);

void split_memory_block_t(memory_block_t* block);

void* find_free_memory_block_t(memory_block_t* node, unsigned int size);

void* buddy_allocate(unsigned int size);

void buddy_free(void* ptr);

#endif // MEMORY_H