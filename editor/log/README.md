# 概要
- 自作エディタをする際に、検証したことやメモなどを書いていく。

## `termios` を用いたコンソールから文字列を表示させないことの検証

### プログラム
- `test_0.sh`
- `test_1.c`
- `test_2.c`

### 検証内容
- コンソールからの入力を行う際、ユーザが入力した内容がそのまま画面に出力される。この役割を果たしているのは、コンソール自身である。この機能をエコーバックと言う。このエコーバックは、デフォルトで有効になっているだけで、それを操作する API を叩けば、設定を変更することができる。

- シェルスクリプトでそれを検証したのが `test_1.sh` である。

- C 言語でエコーバッグを変更するためには、まず現在の値を取得する。(tcgetattr) 次に、変更したいビット値のみ変更し、その値を設定する。(tcsetattr)

- 次に、入力されているパスワードはターミナルに出力されるていないが、文字数だけはわかるような設定をどのように実現するかについて考える。

- コンソールにはモードがあり、カノニカルモードと非カノニカルモードがある。
- カノニカルモード
  - 入力が行単位で行われる。
  - 行区切り文字 (ex. 改行) が入力された時点で有効になる。
  - また、行区切りが入力されるまでの間は行単位の`編集`が可能である。(バックスペースやカーソルキーで入力した内容を編集できる。)
  - この入力待ちで行われている処理は、プログラム側で知ることはできない。最終的にエンターを押下された時に、編集後の値がまとめてプログラムに受け渡される。
  - バッファとしてメモリに蓄えられて処理を遅延させるイメージ。
  - C 言語の argc, argv や Python の sys, input はカノニカルモードの代表例と言える。
- 非カノニカルモード
  - ユーザの入力が即座に有効となる。
  - また、編集機能は無効となる。

- この名称は、cooked モードと raw モードと呼ばれることもある。

### man termios and man stdin and man fgetc

```bash
SYNOPSIS
    #include <termios.h>
    #include <unistd.h>

    int tcgetattr(int fd, struct termios *termios_p);
    int tcsetattr(int fd, int optional_actions,
                    const struct termios *termios_p);

DESCRIPTION
    c_lflag flag constants:
    ICANON Enable canonical mode (described below).

---
SYNOPSIS
       #include <stdio.h>

       extern FILE *stdin;
       extern FILE *stdout;
       extern FILE *stderr;

---
SYNOPSIS
       #include <stdio.h>

       int fgetc(FILE *stream);

---
SYNOPSIS
       #include <ctype.h>

       int iscntrl(int c);

DESCRIPTION
       iscntrl()
              checks for a control character.
```

- 補足だが、`STDIN_FILENO` は int 型の値だが、`stdin` は FILE 型の値である。したがって、`fgetc` の引数として適しているのは、`stdin` である。このことを考えるの面倒くさいときは、`getchar` を使って標準入力から 1 Byte ずつ読み込めば良い。

### 参考
- [パスワード等の入力時にエコーバックをOFFにする (シェルスクリプト)](https://www.qoosky.io/techs/133c9c8cdd)
- [コンソールからのパスワード入力](https://www.mm2d.net/main/prog/c/console-05.html)
- [Linuxシステムコールの勉強(その１０)](https://web-develop.hatenadiary.org/entry/20071112/1194882731)
  - `fprintf(stderr, "")` で文字列を表示する方法以外に、`fflush()` でバッファ内のデータを強制的に吐き出してから、`printf` を実行すると良い。

---

## `termios` を用いたコンソールでプログレス表示をすることの検証

### プログラム
- `test_3.c`
- `test_4.c`
- `test_5.c`
- `test_6.c`

### 検証内容
- プログレスバーの表現方法についてだが、本来であれば「何らかの処理」をしながら表示することになる。この検証では、「何らかの処理」をスリープで表現している。
- エスケープシーケンスの `キャリッジリターン` を使うと、プログレスの状況を表すプログラムを実装できる。

### 参考
- [コンソールによるプログレス表示](https://www.mm2d.net/main/prog/c/console-04.html)

---

## エスケープコードの検証

### プログラム
- `test_7.c`

### 検証内容
- 自作エディタに必要なカーソル移動を検証する。

### 参考
- [ANSIエスケープコード](https://www.mm2d.net/main/prog/c/console-02.html)
- [printfデバッグTips](https://www.mm2d.net/main/prog/c/printf-01.html)
- [パスワードの入力](https://t2y.hatenablog.jp/entry/20090427/1240836509)
  - 標準入力から入力された文字列を表示しない関数が Python に `getpass` というのがある。
  - その内部実装を簡単に解説している記事である。

## termios の各パラメータの設定に関しての検証

### プログラム
- `test_8.c`

### 検証内容
- このプログラムでは、`tm.c_cc[VMIN]` に格納する値は、バッファに何バイトのデータが入ったら、read() を呼び出すかということを決めるための値である。

### 参考
- [Linuxシステムコールの勉強(その１１)](https://web-develop.hatenadiary.org/entry/20071113/1194971862)

---
