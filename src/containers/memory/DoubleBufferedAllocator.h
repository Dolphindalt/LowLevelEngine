#ifndef DOUBLE_BUFFERED_ALLOCATOR_H
#define DOUBLE_BUFFERED_ALLOCATOR_H

#include <cstdint>
#include "src/containers/memory/StackAllocator.h"

// A memory managment class that allows us to store data for frames i and i+1
class DoubleBufferedAllocator
{
private:
    uint8_t current_stack;
    StackAllocator frames[2];
public:
    DoubleBufferedAllocator(size_t size_bytes);
    void swapBuffers();
    void clearCurrentBuffer();
    void *alloc(uint32_t size_bytes);
};

#endif