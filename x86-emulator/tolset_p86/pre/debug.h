#ifndef DEBUG_H_
#define DEBUG_H_

#include <stdio.h>

#ifdef ENABLE_DPRINTF
#define dprintf(fmt, ...) \
    do { \
        fprintf(stderr, "DEBUG (%s): ", __func__); \
        fprintf(stderr, fmt, __VA_ARGS__); \
    } while (0)
#else
#define dprintf(fmt, ...)
#endif

#endif
