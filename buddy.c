#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_MEMORY 1024  
#define MIN_BLOCK_SIZE 32  

char memory[MAX_MEMORY]; 

typedef struct Block {
    size_t size;
    int free;
    struct Block* next;
} Block;

Block* freeList = NULL;

void initBuddySystem() {
    freeList = (Block*)memory;
    freeList->size = MAX_MEMORY;
    freeList->free = 1;
    freeList->next = NULL;
}

Block* findFreeBlock(size_t size) {
    Block* current = freeList;
    while (current != NULL) {
        if (current->free && current->size >= size) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void splitBlock(Block* block) {
    size_t halfSize = block->size / 2;
    
    Block* buddy = (Block*)((char*)block + halfSize);
    buddy->size = halfSize;
    buddy->free = 1;
    buddy->next = block->next;

    block->size = halfSize;
    block->next = buddy;
}

void* allocateMemory(size_t size) {
    if (size == 0 || size > MAX_MEMORY) {
        return NULL;
    }

    // Ensure the requested size is at least MIN_BLOCK_SIZE
    size = (size < MIN_BLOCK_SIZE) ? MIN_BLOCK_SIZE : size;

    size_t actualSize = 1;
    while (actualSize < size ) 
    { // Include Block size in calculation
        actualSize *= 2;
    }

    Block* block = findFreeBlock(actualSize);
    if (block == NULL) {
        return NULL;
    }

    while (block->size > actualSize) {
        splitBlock(block);
    }

    block->free = 0;
    return (void*)((char*)block + sizeof(Block));
}

void mergeBlock(Block* block) {
    Block* buddy = (Block*)((char*)block + block->size);

    if ((char*)buddy - memory < MAX_MEMORY && buddy->free && buddy->size == block->size) {
        block->size *= 2;
        block->next = buddy->next;
        buddy->free = 0;
        mergeBlock(block);  // Recursively merge the block
    }
}

void freeMemory(void* ptr) {
    if (ptr == NULL) {
        return;
    }

    Block* block = (Block*)((char*)ptr - sizeof(Block));
    block->free = 1;
    mergeBlock(block);
}

void displayMemoryStatus() {
    Block* current = freeList;
    printf("Memory status:\n");
    while (current != NULL) {
        printf("Block at %p: Size = %zu, Free = %d\n", (void*)current, current->size, current->free);
        current = current->next;
    }
}

int main() {
    initBuddySystem();

    void* ptr1 = allocateMemory(22);
    void* ptr4 = allocateMemory(512);
    void* ptr2 = allocateMemory(256);
    void* ptr3 = allocateMemory(63);

    printf("\nAfter allocation:\n");
    displayMemoryStatus();

    freeMemory(ptr1);
    freeMemory(ptr2);

    printf("\nAfter deallocation:\n");
    displayMemoryStatus();

    return 0;
}
