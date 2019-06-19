#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "src/containers/memory/StackAllocator.h"

TEST_CASE("Stack Allocator", "[Stack Allocator]")
{
    StackAllocator sa = StackAllocator(sizeof(size_t) * 10);
    REQUIRE(sa.getMarker() == 0);

    SECTION("allocating and deallocating memory")
    {
        size_t *ml = (size_t *)sa.alloc(sizeof(size_t));
        *ml = 5;
        REQUIRE(*ml == 5);
        REQUIRE(sa.getMarker() == sizeof(size_t));

        StackAllocator::Marker first_marker = sa.getMarker();
        (void) sa.alloc(sizeof(size_t));
        StackAllocator::Marker second_marker = sa.getMarker();
        REQUIRE(first_marker != second_marker);
        REQUIRE(second_marker == sizeof(size_t) * 2);
        
        sa.clear();
        REQUIRE(sa.getMarker() == 0);
    }
}