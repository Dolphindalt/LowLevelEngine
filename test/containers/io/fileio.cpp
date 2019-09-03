#include <catch2/catch.hpp>
#include "src/containers/io/fileio.h"

#include <cstring>
#include <iostream>

TEST_CASE("File IO", "[File IO]")
{
    const char *filePath = "test.bin";
    const char *write = "hello my brother";
    size_t file_len = strlen(write);
    size_t written;
    bool result = syncWriteFile(filePath, (const uint8_t *)write, file_len,
    written);
    REQUIRE(result == true);
    REQUIRE(written == strlen(write));
    
    SECTION("sync file reading")
    {
        char buf[file_len];
        size_t bytesRead;
        bool read_result = syncReadFile(filePath, (uint8_t *)buf, file_len, bytesRead);
        REQUIRE(read_result == true);
        REQUIRE(bytesRead == file_len);
    }

    SECTION("sync reading files as a buffer")
    {
        vector<unsigned char> vbuffer;
        bool result = syncReadFileToVectorBuffer(filePath, vbuffer);
        REQUIRE(result == true);
        REQUIRE(vbuffer.size() != 0);
        string sbuffer;
        result = syncReadFileToStringBuffer(filePath, sbuffer);
        REQUIRE(result == true);
        REQUIRE(sbuffer.size() != 0);
    }

    SECTION("async file reading")
    {
        char buf[file_len];
        bool failed = false;
        thread read_thread = asyncReadFile(filePath, (uint8_t *)buf, file_len, 
        [&failed, file_len](uint8_t *buf, size_t bufSize, size_t bytesRead)
        {
            if(bytesRead != file_len)
            {
                failed = true;
            }
        });
        read_thread.join();
        REQUIRE(failed == false);
    }
}