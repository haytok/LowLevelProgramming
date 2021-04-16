#include "clock.h"

// tests.out のサイズが65535 Byte を超えるので、以下のコマンドを使用して圧縮する。
// truncate -s 65533 tests.out
clock_t clock_create(int hour, int minute) {
    clock_t clock;
    char *fmt = "%s:%s";
    char *m, *h;
    // 初期化しないとセグフォになる。
    m = malloc(sizeof(char) * 1024);
    h = malloc(sizeof(char) * 1024);
    // write minute and hour
    hour = write_minute_value(m, minute, hour);
    write_hour_value(h, hour);
    sprintf(clock.text, fmt, h, m);
    return clock;
}

void write_value(char *time, int value) {
    if (value < 10) {
        sprintf(time, "0%d", value);
    } else {
        sprintf(time, "%d", value);
    }
}

clock_t clock_cal(clock_t clock, int value, bool flag) {
    char *m, *h;
    m = malloc(sizeof(char) * 1024);
    h = malloc(sizeof(char) * 1024);
    get_time_from_string(clock, m, h);
    //
    char *fmt = "%s:%s";
    int minute = flag ? atoi(m) + value : atoi(m) - value;
    int hour = atoi(h);
    // write minute and hour
    hour = write_minute_value(m, minute, hour);
    write_hour_value(h, hour);
    sprintf(clock.text, fmt, h, m);
    return clock;
}

clock_t clock_add(clock_t clock, int minute_add) {
    return clock_cal(clock, minute_add, true);
}

clock_t clock_subtract(clock_t clock, int minute_subtract) {
    return clock_cal(clock, minute_subtract, false);
}

bool clock_is_equal(clock_t a, clock_t b) {
    // strcmp で文字列を比較する際に、等しいと 0 が返る。
    return strcmp(a.text, b.text) == 0;
}

void get_time_from_string(clock_t clock, char *m, char *h) {
    char *value;
    value = clock.text;
    strncpy(h, value, 2);
    value += 3;
    strncpy(m, value, 2);
}

int write_minute_value(char *buf, int minute, int hour) {
    if (minute < 0) {
        while (!(minute >= 0 && minute < 60)) {
            minute += 60;
            hour -= 1;
        }
        write_value(buf, minute);
    } else if (minute < 10) {
        sprintf(buf, "0%d", minute);
    } else if (minute >= 10 && minute < 60) {
        sprintf(buf, "%d", minute);
    } else {
        hour += minute / 60;
        minute %= 60;
        write_value(buf, minute);
    }
    return hour;
}

void write_hour_value(char *buf, int hour) {
    if (hour < 0) {
        while (!(hour >= 0 && hour < 24)) {
            hour += 24;
        }
        write_value(buf, hour);
    } else if (hour >= 0 && hour < 10) {
        sprintf(buf, "0%d", hour);
    } else if (hour >= 10 && hour < 24) {
        sprintf(buf, "%d", hour);
    } else {
        hour %= 24;
        write_value(buf, hour);
    }
}
