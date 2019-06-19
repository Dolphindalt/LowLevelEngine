#ifndef STACK_ALLOCATOR_H
#define STACK_ALLOCATOR_H

#include <cstddef>

class StackAllocator
{
public:
    // Represents the top of the stack
    typedef size_t Marker;

    // Constructs a stack allocator given the total size
    explicit StackAllocator(size_t stackSize_bytes);

    // Deallocate my memory
    ~StackAllocator();

    // Allocates a new block given a size from the stack top
    void *alloc(size_t size_bytes);

    // Returns a marker to the current stack top
    Marker getMarker() const;

    // Clears stack to previous marker
    void freeToMarker(Marker marker);

    // Clears the entire stack
    void clear();
private:
    size_t stackSize_bytes;
    size_t *memory_bottom;
    Marker marker;
};

#endif