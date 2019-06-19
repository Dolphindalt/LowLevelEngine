#ifndef POOL_ALLOCATOR_H
#define POOL_ALLOCATOR_H

#include <cstddef>

class PoolAllocator
{
public:
    explicit PoolAllocator();
    explicit PoolAllocator(const size_t elementSize_bytes,
        const size_t numberElements, const size_t alignment);
    ~PoolAllocator();
    void allocPool(const size_t elementSize_bytes, const size_t numberElements,
        const size_t alignment);
    void *getElement();
    void freeElement(void *element);
    void deallocAll();
private:
    size_t poolSize_bytes;
    size_t elementSize_bytes;
    size_t alignment;
    void *pool_memory;
    void **free_memory_list;
};

#endif