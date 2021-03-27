#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <regex.h>
#include <getopt.h>

void do_grep(regex_t *pattern, FILE *file);

static struct option long_options[] = {
    {"ignore-case", no_argument, 0, 'i'},
    {"invert-match", no_argument, 0, 'v'},
    {"help", no_argument, 0, 'h'},
    {0, 0, 0, 0}
};
int opt_invert = 0;

int main(int argc, char **argv) {
    if (argc < 2) {
        fputs("no pattern\n", stderr);
        exit(EXIT_FAILURE);
    }
    printf("argc argc\n");
    // オプションの解析
    int c;
    int option_index = 0;
    int cflags = REG_EXTENDED | REG_NEWLINE;
    while (
        (c = getopt_long(argc, argv, "ivh", long_options, &option_index)) != -1
    ) {
        switch (c) {
            case 'i': {
                cflags |= REG_ICASE;
                break;
            }
            case 'v': {
                opt_invert = 1;
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

    regex_t pattern;
    argc -= optind;
    argv += optind;
    int err;
    err = regcomp(&pattern, argv[0], cflags);
    if (err != 0) {
        char buf[1024];
        regerror(err, &pattern, buf, sizeof(buf));
        puts(buf);
        exit(EXIT_FAILURE);
    }
    argc--;
    if (argc == 0) {
        // 引数にそのまま pattern を入れるとエラーが生じる。
        // do_grep が求めるのは *pattern である。
        do_grep(&pattern, stdin);
    } else {
        for (int i = optind; i < argc; i++) {
            char *path = argv[i];
            FILE *file = fopen(path, "r");
            if (!file) {
                perror(path);
                exit(EXIT_FAILURE);
            }
            do_grep(&pattern, file);
            fclose(file);
        }
    }
}

// cat grep.c | grep <正規表現>
void do_grep(regex_t *pattern, FILE *file) {
    char buf[4096];
    // int matched;
    while (fgets(buf, sizeof(buf), file) != NULL) {
        regmatch_t matched[1];
        if (regexec(pattern, buf, 1, matched, 0) == 0) {
            char *str = buf + matched[0].rm_so;
            regoff_t len = matched[0].rm_eo - matched[0].rm_so;
            fwrite(str, len, 1, stdout);
            fputc('\n', stdout);
        };
        // if (opt_invert) {
        //     matched = !matched;
        // }
        // if (matched) {
        //     puts(buf);
        // }
    }
}
