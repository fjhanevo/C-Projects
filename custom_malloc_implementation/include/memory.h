#ifndef MEMORY_H
#define MEMORY_H

#include <stddef.h>
#include <stdbool.h>

typedef struct block_meta {
    size_t size; 
    bool is_free;
    struct block_meta *next;
} block_meta;

void *mmalloc(size_t size);
void mfree(void *ptr);

#endif // !MEMORY_H
