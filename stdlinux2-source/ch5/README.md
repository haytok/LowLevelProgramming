# 5 章で学んだことや考えたことのログ

## STDOUT_FILENO とは
- `unistd.h` で定義されるマクロのことである。

| FD の番号 | 入出力 | `unistd.h` で定義されるマクロ |
| :---: | :---: | :---: |
| 0 | 標準入力 | STDIN_FILENO |
| 1 | 標準出力 | STDOUT_FILENO |
| 2 | 標準エラー出力 | STDERR_FILENO |

- [プログラムの入出力](https://kaworu.jpn.org/c/%E3%83%97%E3%83%AD%E3%82%B0%E3%83%A9%E3%83%A0%E3%81%AE%E5%85%A5%E5%87%BA%E5%8A%9B)
