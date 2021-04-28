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
    tm.c_lflag    &= ~(ECHO | ECHONL |ICANON);
    tm.c_cc[VMIN]  = 1;
    tm.c_cc[VTIME] = 0;

    tm.c_iflag &= ~ICRNL ; // \r -> \n変換をしない //
    tm.c_oflag &= ~ONLCR ; // \n -> \r変換をしない //
    tm.c_lflag &= ~ISIG  ; // シグナルを無視する   //

    tm.c_iflag &= ~IXOFF ; // c-s, c-qの制御(入力) //
    tm.c_iflag &= ~IXON  ; // c-s, c-qの制御(出力) //

    ioctl(fd_stdin, TCSETAF, &tm);

    result = 0;

    printf("終了する場合はCtrl + x\n");

    while(1)
    {
        // キー入力なし //
        if (read(fd_stdin, &c, 1) == -1)
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
            printf("%02x : %c\r\n",c ,c);
    }

    /* 設定を元に戻す */
    ioctl(fd_stdin, TCSETAF, &tm_save);

    return result;
}
