#include "kernel/memory.h"
#include "libc/bool.h"

memory_block_t* root = NULL;

void initialize_memory(void* memory, unsigned int memory_size){
    root = (memory_block_t*)memory;
    root->left = NULL;
    root->right = NULL;
    root->free = true;
    root->size = memory_size;
}

void split_memory_block_t(memory_block_t* block){
    if(block->size < 2*MIN_BLOCK_SIZE){
        return;
    }

    block->left = (memory_block_t*)((unsigned char*)block+sizeof(memory_block_t));
    block->left->left = NULL;
    block->left->right = NULL;
    block->left->free = true;
    block->left->size = block->size/2;

    block->right = (memory_block_t*)((unsigned char*)block+sizeof(memory_block_t) + block->left->size);
    block->right->left = NULL;
    block->right->right = NULL;
    block->right->free = true;
    block->right->size = block->size/2;
}

void* find_free_memory_block_t(memory_block_t* node, unsigned int size){
    if(!node || !node->free || node->size < size){
        return NULL;
    }

    if(node->size == size){
        node->free = 0;
        return (void*)((unsigned char*)node + sizeof(memory_block_t));
    }

    if(node->size < size * 2){
        return NULL;
    }

    if(!node->left){
        split_memory_block_t(node);
    }

    void* left_memory_block_t = find_free_memory_block_t(node->left, size);
    if(left_memory_block_t){
        return left_memory_block_t;
    }

    void* right_memory_block_t = find_free_memory_block_t(node->right, size);
    return right_memory_block_t;
}

void* buddy_allocate(unsigned int size){
    if(!root){
        return NULL;
    }

    // nearest 2^N number of the size
    unsigned int p = 1;
    while (p < size) {
        p <<= 1;
    }
    size = p;

    memory_block_t* allocated_memory = (memory_block_t*)find_free_memory_block_t(root, size);
    if(!allocated_memory){
        return NULL;
    }

    return (void*)((unsigned char*)allocated_memory+sizeof(memory_block_t));
}

void buddy_free(void* ptr){
    if(!ptr){
        return;
    }

    memory_block_t* block = (memory_block_t*)((unsigned char*)ptr - sizeof(memory_block_t));
    block->free = 1;

    while(block->size < root->size){
        memory_block_t* buddy = (unsigned char*)block - sizeof(memory_block_t) == (unsigned char*)block->left ? block->right : block->left;
        if (!buddy || !buddy->free || buddy->size != block->size) {
            break;
        }

        block->left = NULL;
        block->right = NULL;
        block->size *= 2;
    
        block = ((unsigned char*)block - sizeof(memory_block_t)) == ((unsigned char*)root->left) ? root : (memory_block_t*)((unsigned char*)block - sizeof(memory_block_t));
    }
}