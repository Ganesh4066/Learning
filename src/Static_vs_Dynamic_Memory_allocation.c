#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BUFFER_SIZE 100

// 1. STATIC ALLOCATION: Lives in the .bss segment
// Deterministic. Permanently claims 400 bytes (100 * 4 bytes).
uint32_t static_buffer[BUFFER_SIZE]; 

int main(void) {
    printf("=== Embedded Memory Masterclass ===\n\n");
    printf("[STATIC] Allocated %zu bytes safely at compile-time.\n", sizeof(static_buffer));

    // 2. DYNAMIC ALLOCATION: Lives on the Heap
    // Non-deterministic. Claiming memory at runtime.
    uint32_t *dynamic_buffer = (uint32_t *)malloc(BUFFER_SIZE * sizeof(uint32_t));
    
    // MISTAKE #1 AVOIDED: Always check for a NULL pointer
    if (dynamic_buffer == NULL) {
        printf("[FATAL ERROR] Heap allocation failed. Halting system.\n");
        return EXIT_FAILURE;
    }
    printf("[DYNAMIC] Successfully claimed %zu bytes on the heap.\n", BUFFER_SIZE * sizeof(uint32_t));

    // ... System does work here ...

    // MISTAKE #2 AVOIDED: Always free memory to prevent leaks
    free(dynamic_buffer);
    
    // MISTAKE #3 AVOIDED: Nullify to prevent dangling pointers
    dynamic_buffer = NULL; 
    
    printf("[CLEANUP] Dynamic memory freed safely back to the heap.\n");

    return EXIT_SUCCESS;
}
