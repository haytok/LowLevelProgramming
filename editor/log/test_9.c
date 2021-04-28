#include <sys/ioctl.h>
#include <stdio.h>
#include <asm/termbits.h>

int main()
{
    char c;
    struct termio tm, tm_save;
    int  fd_stdin;
    int  n, result;

    fd_stdin  = fileno(stdin);

    /* 現在の設定を格納 */
    ioctl(fd_stdin, TCGETA, &tm);
    tm_save = tm;

    /* 端末に設定を反映 */
    tm.c_lflag    &= ~(ECHO | ICANON);
    tm.c_cc[VMIN]  = 0; // バッファの単位が 0 なので、即時読み取りを意味する。
    // この値を 0 にすると、ユーザが制御できないほどに高速に画面が流れる。
    // 2 にすると、流れがゆっくりになる。
    tm.c_cc[VTIME] = 1;
    ioctl(fd_stdin, TCSETAF, &tm);

    result = 0;

    printf("終了する場合はCtrl + x\n");

    while(1)
    {
        // キー入力なし //
        if ((n = read(fd_stdin, &c, 1)) == 0)
        {
            printf("入力文字なし\n");
        }

        // システムコール(read())でエラー //
        else if (n == -1)
        {
            perror("read");
            result = 1;
            break ;
        }

        // 入力文字がctrl+xの場合 //
        else if (c == '\x18')
        {
            result = 0;
            break;
        }
        else
            printf("%c\n", c);
    }

    /* 設定を元に戻す */
    ioctl(fd_stdin, TCSETAF, &tm_save);

    return result;
}
