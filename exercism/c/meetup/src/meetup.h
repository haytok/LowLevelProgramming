#ifndef MEETUP_H
#define MEETUP_H

#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <stdint.h>

int meetup_day_of_month(unsigned int year, unsigned int month, const char *week,
                        const char *day_of_week);
int subZeller(int y, int m, int d);
bool leap_year(int year);

#endif
