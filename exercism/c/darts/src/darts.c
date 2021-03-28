#include "darts.h"

uint8_t score(coordinate_t landing_position) {
    uint8_t ans;
    float radius = pow(landing_position[0], 2) + pow(landing_position[1], 2);
    if (radius >= 0 && radius <= 1) {
        ans = 10;
    } else if (radius > 1 && radius <= 25) {
        ans = 5;
    } else if (radius > 25 && radius <= 100) {
        ans = 1;
    } else if (radius > 100) {
        ans = 0;
    }
    return ans;
}
