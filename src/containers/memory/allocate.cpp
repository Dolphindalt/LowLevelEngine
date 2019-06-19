#include "src/containers/memory/allocate.h"

#include "src/debugging/assertions.h"

uintptr_t align_address(uintptr_t address, size_t alignment)
{
    const size_t mask = alignment - 1;
    // power of two alignment
    ASSERT((alignment & mask) == 0);\
    return (address + mask) & ~mask;
}

void *allocate_aligned(const size_t bytes, const size_t alignment)
{
    size_t actual_bytes = bytes + alignment;
    uint8_t *rawptr = new uint8_t[actual_bytes];
    // align and shift block, if no shift, then move and store shift
    uint8_t *aligned_memory = align_pointer(rawptr, alignment);
    if (aligned_memory == rawptr)
        aligned_memory += alignment;
    // determine and store shift
    ptrdiff_t shift = aligned_memory - rawptr;
    ASSERT(shift > 0 && shift <= 256);
    aligned_memory[-1] = static_cast<uint8_t>(shift & 0xFF);
    return aligned_memory;
}

void free_aligned(void *memory)
{
    if(memory)
    {
        // convert to uint8_t ptr
        uint8_t *aligned_memory = reinterpret_cast<uint8_t *>(memory);
        // extract shift
        ptrdiff_t shift = aligned_memory[-1];
        if (shift == 0)
            shift = 256;
        // backtrack to allocated address and delete
        uint8_t *raw_memory = aligned_memory - shift;
        delete [] raw_memory;
    }
}