#include <unistd.h>
#include "memory.h"

// global head pointer
static block_meta *global_head = NULL;

// traverse the list and find a block with an appropriate size
static block_meta *find_free_block(size_t size)
{
    block_meta *current = global_head;

    while (current != NULL) {
        if (current->is_free && current->size >= size) {
            return current;
        }
        // go to next node
        current = current->next;
    }
    return NULL;
}

// helper function to request more memory if find_free_block returns NULL
static block_meta *request_space(size_t size)
{
    // find program break and make a new block
    block_meta *new_blk= sbrk(0);


    // request more memory
    void *request = sbrk(size + sizeof(block_meta));
    
    if (request == (void*) -1) {
        return NULL; 
    }

    // init new block
    new_blk->size = size;
    new_blk->is_free = false;
    new_blk->next = NULL;

    return new_blk;
}


