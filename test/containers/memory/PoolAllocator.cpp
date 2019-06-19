#include <catch2/catch.hpp>
#include "src/containers/memory/PoolAllocator.h"

TEST_CASE("Pool Allocator", "[Pool Allocator]")
{
    PoolAllocator pa = PoolAllocator(sizeof(uint64_t), 10, 4);
    uint32_t *first = (uint32_t *)pa.getElement();
    *first = 0x33333333;
    REQUIRE(first != nullptr);
    REQUIRE(*first == 0x33333333);

    SECTION("successive allocations")
    {
        pa.getElement();
        pa.getElement();
        pa.getElement();
        REQUIRE(first != nullptr);
        REQUIRE(*first == 0x33333333);
    }
    SECTION("freeing an element")
    {
        pa.freeElement(first);
    }
    SECTION("deallocing all memory")
    {
        pa.deallocAll();
    }
}