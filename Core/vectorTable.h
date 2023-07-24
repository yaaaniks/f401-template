#ifndef VECTORTBALE_H
#define VECTORTBALE_H

#include <stdint.h>

extern volatile uint32_t _vectorTable[];

inline void setIsr(uint32_t irq, void (*f)()) {
    _vectorTable[irq + 0x10] = (uint32_t)f;
}

#endif // VECTORTBALE_H