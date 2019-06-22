#include <catch2/catch.hpp>
#include "src/containers/string/CStringTable.h"

TEST_CASE("CString Table", "[CString Table]")
{
    CStringTable leTable;
    SECTION("generating unique hashes")
    {
        CFixedString uid1 = leTable.FixedString("src/assests/game.jpg");
        CFixedString uid2 = leTable.FixedString("src/assets/sprite.png");
        REQUIRE(uid1.getStr() != nullptr);
        REQUIRE(uid2.getStr() != nullptr);
        REQUIRE(uid1.getStr() != uid2.getStr());
    }
}