#include "resistor_color_duo.h"

int color_code(resistor_band_t *bands) {
    char buf1[2], buf2[2];
    sprintf(buf1, "%d", bands[0]);
    sprintf(buf2, "%d", bands[1]);
    return atoi(strcat(buf1, buf2));
}