#include <catch2/catch.hpp>
#include "src/containers/memory/DoubleBufferedAllocator.h"

TEST_CASE("Double Buffered Allocator", "[Double Buffered Allocator]")
{
    DoubleBufferedAllocator dba = DoubleBufferedAllocator(sizeof(uint32_t) * 4);
    SECTION("allocating between different frames")
    {
        (uint32_t *)dba.alloc(sizeof(uint32_t));
        dba.swapBuffers();
        (uint32_t *)dba.alloc(sizeof(uint32_t));
        dba.swapBuffers();
        dba.clearCurrentBuffer();
        dba.swapBuffers();
        dba.clearCurrentBuffer();
    }
}