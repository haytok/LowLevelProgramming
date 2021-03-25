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
