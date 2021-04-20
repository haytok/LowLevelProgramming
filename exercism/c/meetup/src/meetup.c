#include "meetup.h"

int meetup_day_of_month(unsigned int year, unsigned int month, const char *week,
                        const char *day_of_week) {
    char *dayname[] = {
        "Sunday",
        "Monday",
        "Tuesday",
        "Wednesday",
        "Thursday",
        "Friday",
        "Saturday"
    };
    int date[12] = {
        31,
        28,
        31,
        30,
        31,
        30,
        31,
        31,
        30,
        31,
        30,
        31
    };
    int start_date = 1;
    for (int i = start_date; i < start_date + 7; i++) {
        int value = subZeller(year, month, i);
        // printf("Hello %d %s\n", value, dayname[value]);
        if (strcmp(dayname[value], day_of_week) == 0) {
            start_date = i;
            break;
        }
    }
    if (strcmp(week, "teenth") == 0) {
        while (start_date < 20 && start_date + 7 < 20) {
            start_date += 7;
        }
        return start_date;
    } else if (strcmp(week, "first") == 0) {
        return start_date;
    } else if (strcmp(week, "second") == 0) {
        return start_date + 7;
    } else if (strcmp(week, "third") == 0) {
        return start_date + 14;
    } else if (strcmp(week, "fourth") == 0) {
        return start_date + 21;
    } else if (strcmp(week, "last") == 0) {
        int end_date = leap_year(year) ? 29 :date[month-1];
        while (start_date <= end_date && start_date + 7 <= end_date) {
            start_date += 7;
        }
        return start_date;
    }
}

int subZeller(int y, int m, int d){
    if (m < 3) {
        y--;
        m += 12;
    }
    return ( y + y / 4 - y / 100 + y / 400 + (13 * m + 8) / 5 + d) % 7;
}

bool leap_year(int year) {
    if (year % 4 == 0) {
        if (year % 100 == 0) {
            if (year % 400 == 0) {
                return true;
            }
            return false;
        } else {
            return true;
        }
    } else {
        return false;
    }
}
