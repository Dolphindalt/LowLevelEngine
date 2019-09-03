#include "src/containers/io/fileio.h"

#include "src/debugging/logging.h"
#include <cstdio>
#include <fstream>

using std::ifstream;

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

bool syncReadFileToVectorBuffer(const char *filePath, 
    vector<unsigned char> &buffer)
{
    ifstream file(filePath, std::ios::binary);
    if (file.fail())
    {
        WARNING_LOG("Failed to read file to buffer: %s\n", filePath);
        return false;
    }
    file.seekg(0, std::ios::end);
    size_t size = file.tellg();
    file.seekg(0, std::ios::beg);
    size -= file.tellg();
    buffer.resize(size);
    file.read((char *) &(buffer[0]), size);
    file.close();
    return true;
}

bool syncReadFileToStringBuffer(const char *filePath, string &buffer)
{
    ifstream file(filePath, std::ios::binary);
    if (file.fail())
    {
        WARNING_LOG("Failed to read file to buffer: %s\n", filePath);
        return false;
    }
    file.seekg(0, std::ios::end);
    size_t size = file.tellg();
    file.seekg(0, std::ios::beg);
    size -= file.tellg();
    buffer.resize(size);
    file.read((char *) &(buffer[0]), size);
    file.close();
    return true;
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