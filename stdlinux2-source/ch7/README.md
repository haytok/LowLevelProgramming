# 7 章で学んだことや考えたことのログ

## この章で取り扱うライブラリ関数
- [ ] atoi
- [ ] atol

```bash
SYNOPSIS
       #include <stdlib.h>

       int atoi(const char *nptr);
       long atol(const char *nptr);

DESCRIPTION
       The atoi() function converts the initial portion of the string pointed to by nptr to int.  The behavior is the same as

           strtol(nptr, NULL, 10);

       except that atoi() does not detect errors.

       The atol() and atoll() functions behave the same as atoi(), except that they convert the initial portion of the string to their return type of long or long long.

RETURN VALUE
       The converted value.
```

- getopt (man 3 getopt)
- getopt_long (man 3 getopt_long)

```bash
SYNOPSIS
       #include <unistd.h>

       int getopt(int argc, char * const argv[],
                  const char *optstring);

       extern char *optarg;
       extern int optind, opterr, optopt;

       #include <getopt.h>

       int getopt_long(int argc, char * const argv[],
                  const char *optstring,
                  const struct option *longopts, int *longindex);

DESCRIPTION
        Then optind is the index in argv of the first argv-element that is not an option.
```

## この章で取り扱ったライブラリ
- gdb

## テスト方法
- `cat` コマンドでファイル内容を吐き出し、パイプ `|` でストリームを `head` バイナリに入力する。
- `gcc -o head head.c && ./head head.c --lines=5`
- `gcc -o head head.c && ./head head.c --lines 5`
- `gcc -o head head.c && ./head head.c -n5`
- `gcc -o head head.c && ./head head.c -n 5`
- `gcc -o head head.c && ./head head.c --help`
- `gcc -o head head.c && ./head head.c -h`

## この章の流れ
- head コマンドの作成
- オプションの追加
- gdb を使って仕込んだバグの発見と修正

### gdb の解説で使用されていたコマンド集
- run
- backtrace
- frame
- list
- print

## 練習問題
### 7.4.1
- `gcc -Wall -o mytail mytail.c && ./mytail mytail.c -n5`

```bash
void die(char *string) {
    perror(string);
    exit(EXIT_FAILURE);
}

```

- 解説
- こないだの Yahoo のコーディングテストの本を読む本の選択に関する問題と似ている。
- tail コマンドを実装する際のポイントはリングバッファのデータ構造でプログラムを実装することだった。

```text
このコードではリングバッファ（ring buffer）というデータ構造を使っています。 リングバッファは実体としては固定長のバッファなのですが、 末尾まで到達したら最初に戻ってデータを上書きするところが異なります。

tailコマンドの場合、ファイルを読み込みながら常にそのときの末尾10行だけがあれば十分なわけです。 言い換えると、11行目を読んだら1行目は不要になるはずです。 そこで11行目は1行目を書いたところに上書きしてしまえばいいだろうという発想が出てきます。 リングバッファはまさにそのような処理をするためのデータ構造です。 
```

```bash
SYNOPSIS
       #include <stdio.h>

       char *fgets(char *s, int size, FILE *stream);

fgets() reads in at most one less than size characters from stream and stores them into the buffer pointed to by s.  Reading stops after an EOF or a newline.  If a newline is read, it is stored into the buffer.  A terminating null byte ('\0') is stored after the last character in the buffer.
```

### 7.4.2
- ``
