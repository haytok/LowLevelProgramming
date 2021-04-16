#include "series.h"

// results structure
// typedef struct slices {
//    unsigned int substring_count;
//    char **substring;            // array of pointers of dimension substring_count
// } slices_t;

slices_t slices(char *input_text, unsigned int substring_length) {
    slices_t s;
    int length = strlen(input_text);
    if (substring_length == 0) {
        s.substring_count = 0;
    } else {
        s.substring_count = (unsigned int)length - substring_length + 1;
    }
    char *string[s.substring_count];
    s.substring = malloc(sizeof(char *) * s.substring_count);
    for (int i = 0; i < (int)s.substring_count; i++) {
        char *buf;
        buf = malloc(sizeof(char *) * 1024);
        strncpy(buf, input_text, (int)substring_length);
        input_text++;

        // printf("In for, %c %d %s:\n", input_text[i], (int)s.substring_count, buf);

        string[i] = (char *)malloc(sizeof(char) * strlen(buf));
        strcpy(string[i], buf);
    }
    memcpy(s.substring, string, 1024);
    // printf("Hello %d\n", s.substring_count);
    return s;
}
