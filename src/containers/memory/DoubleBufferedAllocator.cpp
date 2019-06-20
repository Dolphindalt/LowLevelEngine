#include "src/containers/memory/DoubleBufferedAllocator.h"

void DoubleBufferedAllocator::swapBuffers()
{
    current_stack = (uint32_t) !current_stack;
}

void DoubleBufferedAllocator::clearCurrentBuffer()
{
    frames[current_stack].clear();
}

void *DoubleBufferedAllocator::alloc(uint32_t size_bytes)
{
    return frames[current_stack].alloc(size_bytes);
}