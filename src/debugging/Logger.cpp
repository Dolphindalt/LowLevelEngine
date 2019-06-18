#include "src/debugging/Logger.h"

#include "src/debugging/termcol.h"

#include <cstdio>

#define LOG_TO_FILE 0

void Logger::init()
{
    #if LOG_TO_FILE
    freopen("log.txt", "w", stderr);
    #endif
}

void Logger::destroy()
{
    #if LOG_TO_FILE
    fclose(stderr);
    #endif
}

void Logger::logWarning(const char *warning, const char *file, unsigned int line)
{
    fprintf(stderr, ANSI_COLOR_YELLOW "[WARNING]: " ANSI_COLOR_RESET "%s, %s at line %d\n", warning, file, line);
}