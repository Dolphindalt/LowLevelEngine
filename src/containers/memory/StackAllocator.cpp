#include "src/containers/memory/StackAllocator.h"

#include "src/debugging/assertions.h"
#include "src/containers/memory/allocate.h"
#include <cstdlib>
#include <cstdio>

StackAllocator::StackAllocator(size_t stackSize_bytes)
: stackSize_bytes(stackSize_bytes),
memory_bottom(malloc(stackSize_bytes)), marker(0)
{
    ASSERT(stackSize_bytes != 0);
}

StackAllocator::~StackAllocator()
{
    free(memory_bottom);
}

void *StackAllocator::alloc(size_t size_bytes)
{
    this->marker += size_bytes;
    ASSERT(this->marker < this->stackSize_bytes);
    uintptr_t new_top = reinterpret_cast<uintptr_t>(memory_bottom) + size_bytes;
    return reinterpret_cast<void *>(new_top);
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