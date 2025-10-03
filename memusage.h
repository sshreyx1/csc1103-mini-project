#ifndef MEMUSAGE_H
#define MEMUSAGE_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

#define MEMUSAGE_PRINT_SIZE(sym) \
    printf("Size of " #sym ": %zu bytes\n", sizeof(sym))

static inline size_t memusage_estimate_stack_inner(volatile const char *outer_addr)
{
    volatile char inner;
    ptrdiff_t diff = outer_addr - &inner;
    if (diff < 0) diff = -diff;
    return (size_t)diff;
}

static inline size_t estimate_stack_frame_bytes(void)
{
    volatile char outer;
    return memusage_estimate_stack_inner(&outer);
}

#endif /* MEMUSAGE_H */
