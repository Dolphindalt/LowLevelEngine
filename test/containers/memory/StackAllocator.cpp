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
    SECTION("allocating different size memory")
    {
        // odd alignment
        uint8_t *some_byte = (uint8_t *)sa.alloc(sizeof(uint8_t));
        *some_byte = 0x55;
        uint32_t *some_word = (uint32_t *)sa.alloc(sizeof(uint32_t));
        *some_word = 0x66334411;
        uint16_t *some_hword = (uint16_t *)sa.alloc(sizeof(uint16_t));
        *some_hword = 0xFFFF;
        REQUIRE(*some_byte == 0x55);
        REQUIRE(*some_word == 0x66334411);
        REQUIRE(*some_hword == 0xFFFF);

        sa.clear();
        // even alignment
        some_word = (uint32_t *)sa.alloc(sizeof(uint32_t));
        *some_word = 0x22000000;
        some_hword = (uint16_t *)sa.alloc(sizeof(uint16_t));
        *some_hword = 0x11AA;
        REQUIRE(*some_word == 0x22000000);
        REQUIRE(*some_hword == 0x11AA);

        sa.clear();
    }
}