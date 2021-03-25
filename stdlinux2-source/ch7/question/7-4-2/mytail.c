#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

void do_tail(FILE *fd, int total_lines, int nlines);
int count_lines(char *path);
void die(char *string);

int escape = 0;
static struct option long_options[] = {
    {"nlines", required_argument, 0, 'n'},
    {0, 0, 0, 0}
};

int main(int argc, char **argv) {
    if (argc < 2) {
        do_tail(stdin, 0, 0);
    }

    // オプションの解析
    int c;
    int option_index = 0;
    int nlines = 0;
    while (
        (c = getopt_long(argc, argv, "n:", long_options, &option_index)) != -1
    ) {
        switch (c) {
            case 'n': {
                nlines = atoi(optarg);
                break;
            }
            case 'h': {
                fprintf(stdout, "Usage: %s [-n LINES] [FILE ...]\n", argv[0]);
                exit(EXIT_SUCCESS);
            }
            case '?': {
                fprintf(stderr, "Usage: %s [-n LINES] [FILE ...]\n", argv[0]);
                exit(EXIT_FAILURE);
            }
        }
    }

    for (int i = optind; i < argc; i++) {
        int total_lines = 0;
        char *path = argv[i];
        total_lines = count_lines(path);
        FILE *fd = fopen(path, "r");
        if (!fd) {
            die(path);
        }
        do_tail(fd, total_lines, nlines);
        if (fclose(fd) != 0) {
            die(path);
        }
    }

    exit(EXIT_SUCCESS);
}

int count_lines(char *path) {
    int total_lines = 1;
    int c;
    FILE *fd = fopen(path, "r");
    if (!fd) {
        die(path);
    }

    while ((c = fgetc(fd)) != EOF) {
        if (c == '\n') {
            total_lines++;
        }
    }

    return total_lines;
}

void do_tail(FILE *fd, int total_lines, int nlines) {
    int c;

    while ((c = fgetc(fd)) != EOF) {
        if (c == 10 && (total_lines > (nlines + 1))) {
            total_lines--;
            continue;
        }
        if ((total_lines == nlines + 1) && putchar(c) < 0) {
            exit(EXIT_FAILURE);
        }
    }
}

void die(char *string) {
    perror(string);
    exit(EXIT_FAILURE);
}

