#include <stdio.h>
#include "memory.h"

int main(void)
{
    printf("--- Malloc Test ---\n\n");

    printf("1. Allocating a single integer\n");
    int *p1 = mmalloc(sizeof(int));
    if (p1 == NULL) {
        printf("Allocation failed!\n");
        return 1;
    }
    *p1 = 42;
    printf("Success: val: %d at adress: %p\n\n", *p1, (void*)p1);

    // === Test Case 2: Multiple Allocations ===
    printf("2. Allocating three more pointers...\n");
    char *p2 = mmalloc(16);
    long *p3 = mmalloc(sizeof(long));
    printf("   p2 Address: %p\n", (void*)p2);
    printf("   p3 Address: %p\n\n", (void*)p3);

    // === Test Case 3: Freeing and Reusing Memory ===
    printf("3. Freeing p2 and re-allocating...\n");
    printf("   Freeing p2 (address %p)...\n", (void*)p2);
    mfree(p2);

    char *p4 = mmalloc(8); // smaller or equal size
    printf("   Allocated p4. Its address should be the same as p2's.\n");
    printf("   p4 Address: %p\n\n", (void*)p4);

    // === Test Case 4: Requesting More Memory from OS ===
    printf("4. Allocating a large block to trigger sbrk()...\n");
    void *p5 = mmalloc(10000);
    if (p5 == NULL) {
        printf("   Large allocation failed!\n");
    } else {
        printf("   Large allocation successful. Address: %p\n\n", p5);
    }
    
    // === Test Case 5: Edge Cases ===
    printf("5. Testing edge cases...\n");
    printf("   Calling mfree(NULL). Should not crash.\n");
    mfree(NULL);
    printf("   Calling mmalloc(0). Should return NULL or a valid pointer.\n");
    void *p6 = mmalloc(0);
    printf("   mmalloc(0) returned: %p\n\n", p6);

    // --- Final Cleanup ---
    printf("--- Test complete. Freeing all remaining memory. ---\n");
    mfree(p1);
    mfree(p3);
    mfree(p4);
    mfree(p5);
    mfree(p6); 
    return 0;
}
