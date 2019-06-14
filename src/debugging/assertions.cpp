#include "src/debugging/assertions.h"

#include "src/debugging/termcol.h"
#include <cstdio>

void reportAssertionFailure(const char *expression, const char *file, unsigned int line)
{
    fprintf(stderr, ANSI_COLOR_RED "[ASSERTION FAILED]" ANSI_COLOR_RESET
        " %s failed in %s on line %d", expression, file, line);
}