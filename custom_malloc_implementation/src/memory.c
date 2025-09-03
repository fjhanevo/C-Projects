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

// custom malloc() implementation 
void *mmalloc(size_t size)
{
    if (size <= 0) {
        return NULL;
    }

    block_meta *block;

    if (global_head == NULL) {
        // request more space
        block = request_space(size);
        if (block == NULL) {
            return NULL;    // only happens if sbrk() fails
        }
        global_head = block;
    }
    else {
        // find a free block
        block = find_free_block(size);
        if (block == NULL) {
            // no free space found so request more
            block = request_space(size);
            if (block == NULL) {
                return NULL;
            }
        }
        else {
            // free block found, mark it as not free
            block->is_free = false;
        }
    }
    // return pointer to the payload
    return (void*)(block + 1);
}

// custom free implementation
void mfree(void *ptr)
{
    // do nothing
    if (ptr == NULL) 
        return;

    // cast generic void ptr to the header, move the ptr back by
    // the size of one block_meta
    block_meta *block = (block_meta*)ptr - 1;

    // mark block as free
    block->is_free = true;

    // add block back into the free list
    block->next = global_head;
    global_head = block;
}
