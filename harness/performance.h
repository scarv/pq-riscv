
#ifndef PERFORMANCE_H
#define PERFORMANCE_H

//! Sample the clock cycle counter (used for timing checks)
uint32_t perf_rdcycle() {
    uint32_t tr;
    asm volatile ("rdcycle %0":"=r"(tr));
    return tr;
}

//! Sample the clock cycle counter (used for timing checks)
uint32_t perf_rdinstret() {
    uint32_t tr;
    asm volatile ("rdinstret %0":"=r"(tr));
    return tr;
}

#endif
