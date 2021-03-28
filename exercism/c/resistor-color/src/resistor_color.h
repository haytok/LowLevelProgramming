#ifndef RESISTOR_COLOR_H
#define RESISTOR_COLOR_H

#define color_code(_COLOR) _COLOR

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
    TYPES
} resistor_band_t;

int *colors();

#endif
