#include "resistor_color_trio.h"

resistor_value_t color_code(resistor_band_t *bands) {
    resistor_value_t actual;
    actual.value = (bands[0] * 10 + bands[1]) * pow(10, bands[2]);
    if (bands[2] < RED) {
        actual.unit = OHMS;
    } else {
        actual.unit = KILOOHMS;
        actual.value /= 1000;
    }
    return actual;
}
