#include <stdio.h>
#include <termios.h>
#include <unistd.h>

// Ubuntu 18.04 のデフォルトで、sudo で何かを実行し、パスワードを求められた時の挙動と似ている。
int main(int argc, char **argv) {
    struct termios term;
    struct termios save; // 設定をもとに戻すために必要。

    tcgetattr(STDIN_FILENO, &term);
    save = term;
    term.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);

    char password[128];
    printf("password:");
    scanf("%s", password);
    printf("%s\n", password);

    tcsetattr(STDIN_FILENO, TCSANOW, &save);
    return 0;
}

// #include <stdio.h>
// #include <ctype.h>
// #include <termios.h>
// #include <unistd.h>
// int main(int argc, char **argv) {
//     int i;
//     int tmp;
//     char password[128];
//     struct termios term;
//     struct termios save;
//     tcgetattr(STDIN_FILENO, &term);
//     save = term;
//     term.c_lflag &= ~ICANON;
//     term.c_lflag &= ~ECHO;
//     tcsetattr(STDIN_FILENO, TCSANOW, &term);
//     for(i = 0; i < sizeof(password) - 1; i++) {
//     tmp = fgetc(stdin);
//     if (tmp < 0 || iscntrl(tmp)) {
//     //   fprintf(stderr, "\n");
//         printf("\n");
//         break;
//     }
//     password[i] = tmp;
//     // fprintf(STD, "*");
//     printf("*");
//     }
//     password[i] = 0;
//     printf("%s\n", password);
//     tcsetattr(STDIN_FILENO, TCSANOW, &save);
//     return 0;
// }
