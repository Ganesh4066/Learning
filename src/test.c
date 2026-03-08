#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("--- Heap Fragmentation Analysis (Raw Pointers) ---\n\n");

    // Phase 1: Sequential Allocation
    // Allocating contiguous chunks to establish the initial heap layout.
    void *p1 = malloc(100);
    void *p2 = malloc(100);
    void *p3 = malloc(100);
    void *p4 = malloc(50);

    printf("[ALLOC] p1: %p | Size: 100\n", p1);
    printf("[ALLOC] p2: %p | Size: 100\n", p2);
    printf("[ALLOC] p3: %p | Size: 100\n", p3);
    printf("[ALLOC] p4: %p | Size: 50\n",  p4);

    // Phase 2: Generating External Fragmentation
    // Freeing p2 creates an isolated "hole" (unsorted bin/fastbin) between p1 and p3.
    // Freeing p4 returns memory to the wilderness (top chunk) or a specific bin.
    printf("\n--- Inducing Fragmentation ---\n");
    
    free(p2);
    printf("[FREE]  Address: %p (100-byte hole created)\n", p2);
    
    free(p4);
    printf("[FREE]  Address: %p (Trailing chunk released)\n", p4);

    // Phase 3: Strategic Re-allocation
    printf("\n--- Allocation Reuse Logic ---\n");

    // Case A: Size exceeds the available hole at p2 (150 > 100).
    // The allocator will likely skip the hole and extend the program break.
    void *p5 = malloc(150);
    printf("[ALLOC] p5: %p | Size: 150 (New segment)\n", p5);

    // Case B: Size matches or is smaller than the hole at p2 (50 <= 100).
    // The allocator may split the 100-byte hole to satisfy this 50-byte request.
    void *p6 = malloc(50);
    printf("[ALLOC] p6: %p | Size: 50 (Reused hole or split chunk)\n", p6);

    // Final Cleanup
    free(p1);
    free(p3);
    free(p5);
    free(p6);

    return 0;
}
