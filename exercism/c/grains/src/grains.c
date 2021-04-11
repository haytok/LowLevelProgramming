#include "grains.h"

uint64_t square(uint8_t index) {
    if (index > 64) {
        return 0;
    }
    return pow(2, (index - 1));
}

uint64_t total(void) {
    uint64_t counts = 0;
    for (int i = 1; i < 65; i++) {
        counts += square(i);
    }
    return counts;
}
