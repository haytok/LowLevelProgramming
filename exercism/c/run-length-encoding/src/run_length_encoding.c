#include "run_length_encoding.h"

char *encode(const char *text) {
    char *ans;
    ans = malloc(sizeof(char) * 1024);
    if (strcmp(text, "") == 0) {
        return ans;
    }

    char *copy_text = strdup(text);
    int length = strlen(copy_text);
    char now_string = copy_text[0];
    int counts = 1;
    int i = 1;
    for (i = 1; i < length; i++) {
        char *buf;
        buf = malloc(sizeof(char) * 2);
        if (now_string == copy_text[i]) {
            counts++;
        } else {
            write_buf(counts, buf, now_string);
            strcat(ans, buf);
            now_string = copy_text[i];
            counts = 1;
        }
        if (i == length - 1) {
            write_buf(counts, buf, now_string);
            strcat(ans, buf);
        }
    }
    return ans;
}

char *decode(const char *data) {
    char *ans;
    ans = malloc(sizeof(char) * 1024);
    if (strcmp(data, "") == 0) {
        return ans;
    }

    char *copy_text = strdup(data);
    int counts = 1;
    while (*copy_text) {
        if (isdigit(*copy_text) != 0) {
            counts = (int)strtol(copy_text, &copy_text, 10);
            continue;
        }
        for (int j = 0; j < counts; j++) {
            char *buf;
            buf = malloc(sizeof(char) * 2);
            sprintf(buf, "%c", *copy_text);
            strcat(ans, buf);
            free(buf);
        }
        counts = 1;
        copy_text++;
    }
    return ans;
}

void write_buf(int counts, char *buf, char now_string) {
    if (counts == 1) {
        sprintf(buf, "%c", now_string);
    } else {
        sprintf(buf, "%d%c", counts, now_string);
    }
}
