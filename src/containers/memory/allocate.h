#ifndef ALLOCATE_H
#define ALLOCATE_H

// TODO: functions here could be inline, need to profile later

#include <cstddef>
#include <cstdint>

// Shift given memory address upwards to ensure it is aligned
uintptr_t align_address(uintptr_t address, size_t alignment);

// Shift given pointer upwards to ensure it is aligned
template <typename T>
inline T *align_pointer(T *ptr, size_t alignment)
{
    const uintptr_t addr = reinterpret_cast<uintptr_t>(ptr);
    const uintptr_t addr_aligned = align_address(addr, alignment);
    return reinterpret_cast<T *>(addr_aligned);
}

void *allocate_aligned(const size_t bytes, const size_t alignment);

void free_aligned(void *memory);

#endif