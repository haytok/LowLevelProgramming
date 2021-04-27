# 概要
- 自作エディタをする際に、検証したことやメモなどを書いていく。

## `termios` を用いたコンソールから文字列を表示させないことの検証

### プログラム
- `test_0.sh`
- `test_1.c`
- `test_2.c`

### 内容
- コンソールからの入力を行う際、ユーザが入力した内容がそのまま画面に出力される。この役割を果たしているのは、コンソール自身である。この機能をエコーバックと言う。このエコーバックは、デフォルトで有効になっているだけで、それを操作する API を叩けば、設定を変更することができる。

- シェルスクリプトでそれを検証したのが `test_1.sh` である。

- C 言語でエコーバッグを変更するためには、まず現在の値を取得する。(tcgetattr) 次に、変更したいビット値のみ変更し、その値を設定する。(tcsetattr)

- 次に、入力されているパスワードはターミナルに出力されるていないが、文字数だけはわかるような設定をどのように実現するかについて考える。

- コンソールにはモードがあり、カノニカルモードと非カノニカルモードがある。
- カノニカルモード
  - 
- 非カノニカルモード
  - 

### man termios

```bash
SYNOPSIS
    #include <termios.h>
    #include <unistd.h>

    int tcgetattr(int fd, struct termios *termios_p);
    int tcsetattr(int fd, int optional_actions,
                    const struct termios *termios_p);
```

### 参考
- [パスワード等の入力時にエコーバックをOFFにする (シェルスクリプト)](https://www.qoosky.io/techs/133c9c8cdd)
- [コンソールからのパスワード入力](https://www.mm2d.net/main/prog/c/console-05.html)
