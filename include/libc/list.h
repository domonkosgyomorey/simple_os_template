#ifndef LIST_H
#define LIST_H

typedef struct list_node_t {
    void* item;
    struct list_node_t* next;
} list_node_t;

typedef struct list_t {
    list_node_t* head;
    unsigned int size; 
} list_t;

#endif // LIST_H