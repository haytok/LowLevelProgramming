#include "two_fer.h"

void two_fer(char *buffer, const char *name) {
    char *fmt = "One for %s, one for me.";
    sprintf(buffer, fmt, name == NULL ? "you" : name);
}
