#include "triangle.h"

// typedef struct {
//    double a;
//    double b;
//    double c;
// } triangle_t;

bool is_equilateral(triangle_t sides) {
    if (sides.a == 0 && sides.b == 0 && sides.c == 0) {
        return false;
    }
    if (sides.a == sides.b && sides.b == sides.c) {
        return true;
    }
    return false;
}

bool is_isosceles(triangle_t sides) {
    if (sides.a == sides.b) {
        return is_triangle(sides.a, sides.c);
    } else if (sides.b == sides.c) {
        return is_triangle(sides.b, sides.a);
    } else if (sides.c == sides.a) {
        return is_triangle(sides.c, sides.b);
    }
    return false;
}

bool is_triangle(double x, double y) {
    return 2 * x > y ? true : false;
}

bool is_scalene(triangle_t sides) {
    if (is_exist(sides)) {
        if (is_equilateral(sides) || is_isosceles(sides)) {
            return false;
        }
        return true;
    } else {
        return false;
    }
}

bool is_exist(triangle_t sides) {
    if (
        is_triple(sides.a, sides.b, sides.c)
        && is_triple(sides.b, sides.c, sides.a)
        && is_triple(sides.c, sides.a, sides.b)
    ) {
        return true;
    }
    return false;
}

bool is_triple(double x, double y, double z) {
    return x + y > z ? true : false;
}
