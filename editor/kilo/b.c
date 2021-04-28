#include <stdio.h>
#include <sys/ioctl.h>

int main(int argc, char *argv[])
{

 struct winsize ws;

/*
 * ioctl(2)システムコールを使ってウィンドウサイズ
 * （ターミナルサイズ）を取得し、構造体winsize wsに
 * 値を保存している。
 */
ioctl(1, TIOCGWINSZ, &ws);

printf("ws_row: %d, ws_col: %d\n", ws.ws_row, ws.ws_col);
}
