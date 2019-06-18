#ifndef ASSERTIONS_H
#define ASSERTIONS_H

#define ASSERTIONS_ENABLED 1
#define STATIC_ASSERTIONS_ENABLED 1

// Logs in stderr a warning giving detail about the failed assertion and its location
void reportAssertionFailure(const char *expression, const char *file, unsigned int line);

// break program then enter debugger
#define DEBUG_BREAK asm volatile ("int3;");

#if ASSERTIONS_ENABLED
#define ASSERT(expr) \
    if (expr) {} \
    else \
    { \
        reportAssertionFailure(#expr, __FILE__, __LINE__); \
        DEBUG_BREAK; \
    }
#else
#define ASSERT(expr)
#endif

#if STATIC_ASSERTIONS_ENABLED
#define _ASSERT_GLUE(a, b) a ## b
#define ASSERT_GLUE(a, b) _ASSERT_GLUE(a, b)
#define STATIC_ASSERT(expr) \
enum \
{ \
    ASSERT_GLUE(g_assert_fail_, __LINE__) \
        = 1 / (int)(!!(expr)) \
}
#else
#define STATIC_ASSERT(expr)
#endif

#endif