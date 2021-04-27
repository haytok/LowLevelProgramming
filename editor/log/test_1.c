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
