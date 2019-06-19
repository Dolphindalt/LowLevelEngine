#include "src/containers/memory/PoolAllocator.h"

#include "src/debugging/assertions.h"
#include "src/containers/memory/allocate.h"

PoolAllocator::PoolAllocator()
: poolSize_bytes(0), elementSize_bytes(0), alignment(0), pool_memory(nullptr),
free_memory_list(nullptr)
{}

PoolAllocator::~PoolAllocator()
{
    deallocAll();
}

PoolAllocator::PoolAllocator(const size_t elementSize_bytes,
    const size_t numberElements, const size_t alignment)
{
    pool_memory = free_memory_list = nullptr;
    allocPool(elementSize_bytes, numberElements, alignment);
    // element size at least same size of void *
    ASSERT(elementSize_bytes >= sizeof(void *));
    // element size mutilpe of alignment
    ASSERT(elementSize_bytes % alignment == 0);
    // alignment is a power of 2
    ASSERT((alignment & (alignment - 1)) == 0);
}

void PoolAllocator::allocPool(const size_t elementSize_bytes, 
    const size_t numberElements, const size_t alignment)
{
    ASSERT(pool_memory == nullptr);

    this->elementSize_bytes = elementSize_bytes;
    this->alignment = alignment;
    // element size mutilpe of alignment
    ASSERT(elementSize_bytes % alignment == 0);
    // alignment is a power of 2
    ASSERT((alignment & (alignment - 1)) == 0);

    poolSize_bytes = (elementSize_bytes * numberElements) + alignment;

    pool_memory = allocate_aligned(elementSize_bytes * numberElements, alignment);
    ASSERT(pool_memory != nullptr);
    // view memory as a buffer of void *
    free_memory_list = static_cast<void **>(pool_memory);
    // get the address at the end of the memory block
    uintptr_t end_address = reinterpret_cast<uintptr_t>(free_memory_list) + (elementSize_bytes * numberElements);
    for(size_t element_count = 0; element_count < numberElements; element_count++)
    {
        uintptr_t current_address = reinterpret_cast<uintptr_t>(free_memory_list) + (element_count * elementSize_bytes);
        uintptr_t next_address = current_address + elementSize_bytes;
        // cast address of current to void**
        void **current_memory = reinterpret_cast<void **>(current_address);
        if (next_address >= end_address)
            *current_memory = nullptr;
        else
            *current_memory = reinterpret_cast<void *>(next_address);
    }
}

void *PoolAllocator::getElement()
{
    if(pool_memory == nullptr)
        return nullptr;
    
    if (free_memory_list != nullptr)
    {
        void *block = reinterpret_cast<void *>(free_memory_list);
        free_memory_list = static_cast<void **>(*free_memory_list);
        return block;
    }
    else
        return nullptr;
}

void PoolAllocator::freeElement(void *block)
{
    if (block == nullptr)
        return;
    
    if (pool_memory == nullptr)
        return;
    
    if (free_memory_list == nullptr)
    { // the free list is empty
        free_memory_list = reinterpret_cast<void **>(block);
        *free_memory_list = nullptr;
    }
    else
    {
        void **returned_block = free_memory_list;
        free_memory_list = reinterpret_cast<void **>(block);
        *free_memory_list = reinterpret_cast<void *>(returned_block);
    }
}

void PoolAllocator::deallocAll()
{
    free_aligned(pool_memory);
    pool_memory = free_memory_list = nullptr;
}