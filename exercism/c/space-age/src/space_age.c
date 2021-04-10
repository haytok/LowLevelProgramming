#include "space_age.h"

float t[COUNTS] = {
    0.2408467,
    0.61519726,
    31557600,
    1.8808158,
    11.862615,
    29.447498,
    84.016846,
    164.79132
};

float age(planet_t planet, int64_t seconds) {
    return planet == EARTH ? seconds / t[planet] : seconds / (t[EARTH] * t[planet]);
}
