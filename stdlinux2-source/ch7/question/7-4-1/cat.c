#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

void do_cat(FILE *fd);
void die(char *string);

int escape = 0;
static struct option long_options[] = {
    {"escape", no_argument, 0, 'e'},
    {0, 0, 0, 0}
};

int main(int argc, char **argv) {
    if (argc < 2) {
        do_cat(stdin);
    }

    // オプションの解析
    int n = 0;
    int c;
    int option_index = 0;
    while (
        (c = getopt_long(argc, argv, "e", long_options, &option_index)) != -1
    ) {
        switch (c) {
            case 'e': {
                escape = 1;
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
        char *path = argv[i];
        FILE *fd = fopen(path, "r");
        if (!fd) {
            die(path);
        }
        do_cat(fd);
        if (fclose(fd) != 0) {
            die(path);
        }
    }

    exit(EXIT_SUCCESS);
}

void do_cat(FILE *fd) {
    int c;

    while ((c = fgetc(fd)) != EOF) {
        if (escape) {
            if (c == 10) {
                printf("$\n");
            } else if (c == 9) {
                printf("\\t");
            }
        }
        if (putchar(c) < 0) {
            exit(EXIT_FAILURE);
        }
    }

    // while ((c = fgetc(fd)) != EOF) {
    //     switch (c) {
    //         case '\n': {
    //             if (fputs("$\n", stdout) < 0) {
    //                 exit(EXIT_FAILURE);
    //             }
    //             break;
    //         }
    //         case '\t': {
    //             if (fputs("\\t", stdout)) {
    //                 exit(EXIT_FAILURE);
    //             }
    //             break;
    //         }
    //         default: {
    //             if (putchar(c) < 0) {
    //                 exit(EXIT_FAILURE);
    //             }
    //             break;
    //         }
    //     }
    // }
}

void die(char *string) {
    perror(string);
    exit(EXIT_FAILURE);
}
