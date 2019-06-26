#include <catch2/catch.hpp>
#include "src/resources/Resource.h"
#include "src/containers/string/CStringTable.h"

TEST_CASE("Resource Class", "[Resource Class]")
{
    const char *uid = "some string in memory";
    int tval = 5;
    int *memsim = &tval;
    Resource<int> resource = Resource<int>(uid, memsim);
    REQUIRE(resource.getRefs() == 1);

    SECTION("Reference counting test")
    {
        Resource<int> resource2 = Resource<int>(uid, memsim);
        REQUIRE(resource2.getRefs() == 2);
        Resource<int> resource3 = Resource<int>(resource2);
        REQUIRE(resource.getRefs() == 3);
    }
    REQUIRE(resource.getRefs() == 1);
}