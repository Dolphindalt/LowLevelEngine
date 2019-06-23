#include "src/containers/io/fileio.h"

#include <cstdio>

bool syncWriteFile(const char *filePath, const uint8_t *buffer, size_t bufferSize,
    size_t &bytesWritten)
{
    FILE *handle = fopen(filePath, "wb");
    if(handle)
    {
        size_t written = fwrite(buffer, sizeof(uint8_t), bufferSize, handle);
        int err = ferror(handle);
        fclose(handle);
        if (err == 0)
        {
            bytesWritten = written;
            return true;
        }
    }
    return false;
}

bool syncReadFile(const char *filePath, uint8_t *buffer, size_t bufferSize,
    size_t &rBytesRead)
{
    FILE *handle = fopen(filePath, "rb");
    if (handle)
    {
        // BLOCK until all data has been read
        size_t bytesRead = fread(buffer, sizeof(uint8_t), bufferSize, handle);
        int err = ferror(handle);
        fclose(handle);
        if(err == 0)
        {
            rBytesRead = bytesRead;
            return true;
        }
    }
    rBytesRead = 0;
    return false;
}

thread asyncReadFile(const char *filePath, uint8_t *buffer, size_t bufferSize,
    function<void(uint8_t *buf, size_t bufSize, size_t bytesRead)> callback)
{
    auto fileRead = [filePath, buffer, bufferSize, callback]()
    {
        size_t bytesRead;
        bool success = syncReadFile(filePath, buffer, bufferSize, bytesRead);
        if(success)
        {
            callback(buffer, bufferSize, bytesRead);
        }
    };
    thread asyncRead(fileRead);
    return asyncRead;
}