#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <ctype.h>

int main(int argc, char **argv) {
    struct termios term;
    struct termios save; // 設定をもとに戻すために必要。

    tcgetattr(STDIN_FILENO, &term);
    save = term;
    term.c_lflag &= ~ECHO; // エコーバッグを無効にする
    term.c_lflag &= ~ICANON; // 非カノニカルモードにする
    tcsetattr(STDIN_FILENO, TCSANOW, &term);

    int i = 0;
    char password[128];
    printf("password:");
    for (i = 0; i < sizeof(password); i++) {
        char tmp = getchar();
        if (tmp < 0 || iscntrl(tmp)) {
            printf("\n");
            break;
        }
        password[i] = tmp;
        printf("_");
    }
    password[i] = 0;
    printf("%s\n", password);

    tcsetattr(STDIN_FILENO, TCSANOW, &save);
    return 0;
}
