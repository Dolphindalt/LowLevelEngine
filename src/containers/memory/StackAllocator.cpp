#include "src/containers/memory/StackAllocator.h"

#include "src/debugging/assertions.h"
#include <cstdlib>

StackAllocator::StackAllocator(size_t stackSize_bytes)
: stackSize_bytes(stackSize_bytes),
memory_bottom((size_t *)malloc(stackSize_bytes)), marker(0)
{

}

StackAllocator::~StackAllocator()
{
    free(memory_bottom);
}

void *StackAllocator::alloc(size_t size_bytes)
{
    this->marker += size_bytes;
    ASSERT(this->marker < this->stackSize_bytes);
    return (void *)(memory_bottom + size_bytes);
}

StackAllocator::Marker StackAllocator::getMarker() const
{
    return this->marker;
}

void StackAllocator::freeToMarker(StackAllocator::Marker marker)
{
    this->marker = marker;
}

void StackAllocator::clear()
{
    this->marker = 0;
}