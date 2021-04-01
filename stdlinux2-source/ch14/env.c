#include <stdio.h>
#include <stdlib.h>

extern char **environ;

int main(int argc, char **argv) {
    char **e;
    for (e = environ; environ; e++) {
        printf("%s\n", *e);
    }
    exit(EXIT_SUCCESS);
}
