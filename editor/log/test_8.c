 #include <sys/ioctl.h>
 #include <stdio.h>
 #include <asm/termbits.h>

 int main()
 {
    char c[BUFSIZ];
    struct termio tm, tm_save;
    int  inputNum;
    int  fd_stdin, fd_stdout;

    fd_stdin  = fileno(stdin);
    fd_stdout = fileno(stdout);

    /* 現在の設定を格納 */
    ioctl(fd_stdin, TCGETA, &tm);
    tm_save = tm;

    /* 入力したい文字数を取得 */
    printf("何文字入力しますか？");
    fscanf(stdin,"%d", &inputNum);

    /* 端末に設定を反映 */
    tm.c_lflag &= ~ICANON;
    tm.c_cc[VMIN] = inputNum; // この VMIN のパラメータ設定がこのプログラムにおけるポイントである。
    ioctl(fd_stdin, TCSETAF, &tm);

    printf("%d文字入力してください？", inputNum);
    fflush(stdout);
    read(fd_stdin, &c, inputNum);

    // 整形用 //
    write(fd_stdout, "\n", 1);

    write(fd_stdout, c, inputNum);

    // 整形用 //
    write(fd_stdout, "\n", 1);

    /* 設定を元に戻す */
    ioctl(fd_stdin, TCSETAF, &tm_save);

    return 0;
}
