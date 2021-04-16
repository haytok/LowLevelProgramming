#ifndef CLOCK_H
#define CLOCK_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <stdint.h>

#define MAX_STR_LEN (5 + 1)     // "##:##\0"

typedef struct {
   char text[MAX_STR_LEN];
} clock_t;

clock_t clock_create(int hour, int minute);
clock_t clock_add(clock_t clock, int minute_add);
clock_t clock_subtract(clock_t clock, int minute_subtract);
bool clock_is_equal(clock_t a, clock_t b);

void write_value(char *time, int value);
void get_time_from_string(clock_t clock, char *m, char *h);
int write_minute_value(char *buf, int minute, int hour);
void write_hour_value(char *buf, int hour);
clock_t clock_cal(clock_t clock, int value, bool flag);

#endif
