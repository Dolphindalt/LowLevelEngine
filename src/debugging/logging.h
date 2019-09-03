#ifndef LOGGING_H
#define LOGGING_H

#include "src/debugging/termcol.h"
#include <cstdio>

#define INFO_LOG(_f, ...) fprintf(stderr, ANSI_COLOR_GREEN "[Info]: " \
    ANSI_COLOR_RESET _f "\n", ##__VA_ARGS__);

#define WARNING_LOG(_f, ...) fprintf(stderr, ANSI_COLOR_YELLOW "[Warning]: " \
    ANSI_COLOR_RESET _f "\n", ##__VA_ARGS__);

#define WARNING_LOGV(_f, ...) fprintf(stderr, ANSI_COLOR_YELLOW "[Warning]: " \
    ANSI_COLOR_RESET _f " at line %d in %s\n", __LINE__, __FILE__, ##__VA_ARGS__);

#define ERROR_LOG(_f, ...) fprintf(stderr, ANSI_COLOR_RED "[Error]: " \
    ANSI_COLOR_RESET _f "\n", ##__VA_ARGS__);

#define ERROR_LOGV(_f, ...) fprintf(stderr, ANSI_COLOR_RED "[Error]: " \
    ANSI_COLOR_RESET _f " at line %d in %s\n", __LINE__, __FILE__, ##__VA_ARGS__);

#endif