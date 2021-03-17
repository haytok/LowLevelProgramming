# 5 章で学んだことや考えたことのログ

## STDOUT_FILENO とは
- `unistd.h` で定義されるマクロのことである。

| FD の番号 | 入出力 | `unistd.h` で定義されるマクロ |
| :---: | :---: | :---: |
| 0 | 標準入力 | STDIN_FILENO |
| 1 | 標準出力 | STDOUT_FILENO |
| 2 | 標準エラー出力 | STDERR_FILENO |

- [プログラムの入出力](https://kaworu.jpn.org/c/%E3%83%97%E3%83%AD%E3%82%B0%E3%83%A9%E3%83%A0%E3%81%AE%E5%85%A5%E5%87%BA%E5%8A%9B)

## exit() 関数の引数に関して
- `man exit` を読んでみると、以下のようにあり、0, 1 に対するマクロが定義されている。

```bash
The  C  standard specifies two constants, EXIT_SUCCESS and EXIT_FAILURE, that may be passed to exit() to indicate successful or unsuccessful termination, respectively.
```

- ちなみに、この値を printf などで確認すると以下のようになる。

| Status | `int status` | `stdlib.h` で定義されるマクロ |
| :---: | :---: | :---: |
| 成功 | 0 | EXIT_SUCCESS |
| 失敗 | 1 | EXIT_FAILURE |

- [言語のexit関数の使い方](https://kaworu.jpn.org/c/C%E8%A8%80%E8%AA%9E%E3%81%AEexit%E9%96%A2%E6%95%B0%E3%81%AE%E4%BD%BF%E3%81%84%E6%96%B9)
