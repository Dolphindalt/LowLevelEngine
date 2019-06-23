#ifndef FILEIO_H
#define FILEIO_H

#include <cstdint>
#include <cstddef>
#include <functional>
#include <thread>

using std::function;
using std::thread;

/**
 * Defining these functions here and not using standard library functions will 
 * allow for easier porting if cross platforming becomes an issue.
 */

bool syncWriteFile(const char *filePath, const uint8_t *buffer, size_t bufferSize,
    size_t &bytesWritten);

bool syncReadFile(const char *filePath, uint8_t *buffer, size_t bufferSize,
    size_t &bytesRead);

thread asyncReadFile(const char *filePath, uint8_t *buffer, size_t bufferSize,
    function<void(uint8_t *buf, size_t bufSize, size_t bytesRead)> callback);

#endif