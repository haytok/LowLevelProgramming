#ifndef RESISTOR_COLOR_TRIO_H
#define RESISTOR_COLOR_TRIO_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct resistor_value_t resistor_value_t;

typedef enum {
    BLACK,
    BROWN,
    RED,
    ORANGE,
    YELLOW,
    GREEN,
    BLUE,
    VIOLET,
    GREY,
    WHITE,
} resistor_band_t;

typedef enum {
    OHMS,
    KILOOHMS,
} register_unit_t;

struct resistor_value_t {
    int value;
    register_unit_t unit;
};

resistor_value_t color_code(resistor_band_t *bands);

#endif
