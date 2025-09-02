#ifndef MEMORY_H
#define MEMORY_H

#include <stddef.h>
#include <stdbool.h>

typedef struct block_meta {
    size_t size; 
    bool is_free;
    struct block_meta *next;
} block_meta;

static block_meta *find_free_block(size_t size);
static block_meta *request_space(size_t size);
void *mmalloc(size_t size);
void mfree(void *ptr);

#endif // !MEMORY_H
