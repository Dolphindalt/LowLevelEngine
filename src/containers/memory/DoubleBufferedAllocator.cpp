#include "src/containers/memory/DoubleBufferedAllocator.h"

#include "src/debugging/assertions.h"

DoubleBufferedAllocator::DoubleBufferedAllocator(size_t size_bytes)
: current_stack(0),
frames({ StackAllocator(size_bytes), StackAllocator(size_bytes) })
{}

void DoubleBufferedAllocator::swapBuffers()
{
    current_stack ^= 0x01;
    ASSERT(current_stack == 0 || current_stack == 1);
}

void DoubleBufferedAllocator::clearCurrentBuffer()
{
    frames[current_stack].clear();
}

void *DoubleBufferedAllocator::alloc(uint32_t size_bytes)
{
    return frames[current_stack].alloc(size_bytes);
}