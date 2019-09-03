#include <catch2/catch.hpp>
#include "src/debugging/logging.h"

TEST_CASE("Logging", "[Logs]")
{
    INFO_LOG("This is some info with a number: %d", 5);
    WARNING_LOG("Warning xd");
    ERROR_LOG("Error log test");
    ERROR_LOGV("Error with file and line");
}