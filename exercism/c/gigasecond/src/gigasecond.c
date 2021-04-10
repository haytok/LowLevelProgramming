#include "gigasecond.h"

time_t gigasecond_after(time_t t) {
    t += 1000000000;
    return t;
}
