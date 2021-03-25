#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

void do_head(FILE *file, int n);
void die(char *path);

static struct option long_options[] = {
    {"lines", required_argument, 0, 'n'},
    {"help", no_argument, 0, 'h'},
    {0, 0, 0, 0}
};

// cat head.c > 
// ./head 5 file_name
int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stdout, "Usage: %s [-n LINES] [FILE ...]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    // まずオプションの解析をする必要がある
    int n = 0;
    int c;
    int option_index = 0;
    while (
        (c = getopt_long(argc, argv, "n:h", long_options, &option_index)) != -1
    ) {
        switch (c) {
            case 'n': {
                n = atoi(optarg);
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

    if (argc == 2) {
        do_head(stdin, n);
    } else {
        for (int i = optind; i < argc; i++) {
            char *path = argv[i];
            printf("%s\n", path);
            FILE *file = fopen(path, "r");
            if (!file) {
                die(path);
            }
            do_head(file, n);
        }
    }
    exit(EXIT_SUCCESS);
}

void do_head(FILE *file, int n) {
    int c;
    while (n != 0 && ((c = fgetc(file)) != EOF)) {
        if (putchar(c) < 0) {
            exit(EXIT_FAILURE);
        }
        if (c == '\n') {
            n--;
        }
    }
}

void die(char *path) {
    perror(path);
    exit(EXIT_FAILURE);
}
