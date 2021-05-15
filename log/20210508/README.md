# 2021/05/08

## 概要
- Linux Kernel のシステムコール周りのソースコードを読んだ。Linux Kernel のコードリーディングの過程で学んだことのログを残す。
- 主に `write` と `socket` のシステムコール周りのコードリーディングを行った。

## 知ったことや学んだこと

### ssize_t と size_t の違い
- `size_t` は、`unsigned` な整数値である、つまり、負の数は扱わない。
- `ssize_t` は、`signed` な整数値である、つまり、負の数はを扱う。エラーを表現することができる、

### システムコールの socket() の引数に関して
- `/usr/include/sys/socket.h` を確認すると、 `/usr/include/bits/socket.h` にアドレスファミリーの値が定義されていることがわかる。

```bash
SYNOPSIS
       #include <sys/types.h>          /* See NOTES */
       #include <sys/socket.h>

       int socket(int domain, int type, int protocol);
```

#### 参考
- [PF_INETとAF_INETの微妙な違い](https://www.khstasaba.com/?p=401)


### システムコール番号
- そもそも、`syscall()` というシステムコールが存在する。
- 以下のマニュアルを読むと、システムコールに対応する番号を指定して `syscall()` を呼び出すと、番号に対応したシステムコールを呼び出すことができる。

```bash
SYNOPSIS
       #define _GNU_SOURCE         /* See feature_test_macros(7) */
       #include <unistd.h>
       #include <sys/syscall.h>   /* For SYS_xxx definitions */

       long syscall(long number, ...);

DESCRIPTION
       syscall()  is  a  small  library  function  that invokes the system call whose assembly language interface has the specified number with the specified arguments.
       Employing syscall() is useful, for example, when invoking a system call that has no wrapper function in the C library.

       syscall() saves CPU registers before making the system call, restores the registers upon return from the system call, and stores any error code returned  by  the
       system call in errno(3) if an error occurs.

       Symbolic constants for system call numbers can be found in the header file <sys/syscall.h>.
```

- 日本語訳は以下になる。

```text
syscall() は、システムコールを起動する小さなライブラリ関数で、 number で指定されたアセンブ
リ言語インターフェースのシステムコールを、指定された引き数をつけて実行する。 syscall()  が
役に立つのは、例えば  C ライブラリにラッパー関数が存在しないシステムコールを呼び出したい場
合である。
```

- では、システムコール番号はどこで定義されているかと言うと、以下の順序でヘッダファイルを辿ると見つけることができる。

- `/usr/include/sys/syscall.h`
- `/usr/include/bits/syscall.h` 
- `/usr/include/asm/unistd.h`
- `/usr/include/asm/unistd_64.h`
  - `#define __NR_write 1` のようにそれっぽい値が定義されていることがわかる。
- `/usr/include/bits/syscall.h`
  ```bash
  #ifdef __NR_write
  # define SYS_write __NR_write
  #endif
  ```

- おそらく以下の `Linux System Call Table` によると、そのシステムコール番号がレジスタの `rax` に格納される。
- これを用いた内容が`はじめて学ぶバイナリ解析`の p.104 あたりから書かれている。(突然連想ゲームのように思い出した。) 具体的には、 write のシステムコールを呼び出すアセンブリは以下である。この本では、32 bit 用でオブジェクトファイルを作成している。したがって、前述で述べた流れで 32 bit の write システムコール番号を `/usr/include/asm/unistd_32.h` から確認すると、`4` であることがわかる。

```asm
mov eax, 0x4
... (第二引数、第三引数に対するアセンブリが書かれる)
```

#### 参考
- [Linux System Call Table](https://chromium.googlesource.com/chromiumos/docs/+/master/constants/syscalls.md)
- [6-8 演習: 画面に "Hi" と表示しよう](https://github.com/dilmnqvovpnmlib/BinaryAnalysisBook/tree/main/s6)
- [bionic (2) syscall.2.gz](http://manpages.ubuntu.com/manpages/bionic/ja/man2/syscall.2.html)


### 【Linux】ユーザープログラムにおけるシステムコール呼び出し の記事を読んで新しく学んだこと
- システムコールはソフトウェア割り込み (例外) を呼び出す必要があるので、CPU 命令が必要となる。したがって、64 bit CPU では、SYSENTER 命令を使用する。
- また、Linux では、割り込み番号を 128 に指定して、`INT 0x80` を実行する。 
- システムコールの引数が 6 個までである理由は、システムコールで受け取った引数を渡す CPU の汎用レジスタに限りがあるからである。

#### 参考
- [【Linux】ユーザープログラムにおけるシステムコール呼び出し](https://softwaretechnique.jp/linux/systemcall/sc_01.html)


### 64bitのOS + C言語でライブラリを使わずにHello Worldをしてみた
- `#include` を宣言せずに、アセンブリを書いて、コンパイラでリンクさせて Hello World する記事の解説だった。記事は参考の箇所に記載している。

#### 検証プログラム
- `test_3.c`
- `test_3.asm`

- test_3.c

```c
void hello(char *string, int len);

int main (){
  char *string = "Hello Asm!\n";
  hello(string, 11);
  return 0;
}
```

- test_3.asm


```asm
bits 64

global hello

hello:
  mov rdx, rsi
  mov rsi, rdi
  mov rax, 1
  mov rdi, 1
  syscall
  ret
```

- `mov rdx, rsi` に関して
  - rsi は Chronium OS Docs が参考になる。
  - hello 関数の第二引数の値はアセンブリで言うと arg1 の rsi に該当する。
  - 格納先のレジスタは Assembly Register Calling Convention Tutorial が参考になる。
  - Third Argument: RDX

- `mov rsi, rdi` に関して
  - rdi は Chronium OS Docs が参考になる。
  - hello 関数の第一引数の値はアセンブリで言うと arg0 の rdi に該当する。
  - 格納先のレジスタは Assembly Register Calling Convention Tutorial が参考になる。
  - Second Argument: RSI

- `mov rdi, 1`
  - `write システムコール` を呼び出す際の第一引数に 1 (STDOUT_FILENO: 標準出力) を代入している。
  - 格納先のレジスタは Assembly Register Calling Convention Tutorial が参考になる。
  - First Argument: RDI

- `mov rax, 1` に関して
  - システムコール番号を rax に代入する。

- Makefile

```bash
$ nasm -f elf64 -o syscall.o syscall.asm // オブジェクトファイルの作成
$ gcc -c test_3.c // -c オプションを付けることでリンクを行わない
$ gcc test_3.o syscall.o // リンク
$ ./a.out // 実行
Hello Asm!
```

#### 参考
- [64bitのOS + C言語でライブラリを使わずにHello Worldをしてみた](https://qiita.com/Juju_62q/items/2f4611461431a1110736)


### 前節のプログラムを修正して 32 bit 用でコンパイルして実行してみた
- 用意したファイルは以下である。
- そもそも、モチベーションとしては、`syscall.asm` の `syscall` を `int 0x80` に変更しても動作するのではないかと考えたことがキッカケである。
- これは、間違いである。32 bit であれば、システムコールの呼び出しを `int 0x80` 行える。しかし、64 bit では `syscall` で呼び出しを行わなければならない。
- 以下は 3 つ目の記事の引用である。

> x86 Linux の 32bit と 64bit ではシステムコールの呼び出し方法と、 システムコール番号が異なります。システムコールの呼び出しは、 32bit では int 0x80 でソフトウェア割り込みを実行することでシステムコールを呼び出していますが、64bit では syscall 命令を実行します。

- こうして、システムコールの呼び出しを 32 bit 用 (int 0x80) に変更して、コンパイルしてリンクを行い、実行ファイルを作成しようと試みたが、諸々のエラーが生じた。例えば、レジスタやシステムコール番号の違いやコンパイルする際のバイナリの bit の指定方法である。
- これらを修正して実行し直したが、上手くいかなったので、とりあえず[Cとアセンブラを組み合わせてコンパイルする](https://kobapan.hatenadiary.org/entry/20090524/1258476318)の記事を参考に引数から受け取って処理を走らせるプログラムで検証した。

#### 検証プログラム 1
- `test_4.c`
- `test_4.asm`

- test_4.c

```c
int hello(int value);

int main (){
    return hello(10);
}
```

- test_4.asm

```asm
bits 32

global hello

hello:
  mov edx, [esp+4] // 関数の引数の値を取得して、レジスタに格納する
  add edx, 0x1
  mov eax, edx
  ret
```

- 確認

```bash
make test_4
./test_4.out
echo $?
```

#### 検証プログラム 2
- 検証プログラム 1 を応用して関数の引数に渡された文字列を `write システムコール` で表示するアセンブリとプログラムを実装した。

- `test_5.c`
- `test_5.asm`

- test_5.c

```
void hello(char *string, int len);

int main (){
    char *string = "ABCD\n";
    hello(string, 5);
    return 0;
}
```

- test_5.asm

```
bits 32

global hello

hello:
  mov eax, 0x4
  mov ebx, 0x1
  mov ecx, [esp+4]
  mov edx, [esp+8]
  int 0x80
  add esp, 0x4
  ret
```

- 確認

```bash
make test_5
```

- アセンブリにバグがあり、思った出力が出ない時は、`strace` コマンドを使用してデバッグを行った。
- strace を活用して write システムコールを呼び出す際の引数が適切かを確認した。

#### 参考
- [64bitのOS + C言語でライブラリを使わずにHello Worldをしてみた](https://qiita.com/Juju_62q/items/2f4611461431a1110736)
- [Assembly Register Calling Convention Tutorial](https://www.raywenderlich.com/615-assembly-register-calling-convention-tutorial)
- [Linux System Call Table](https://chromium.googlesource.com/chromiumos/docs/+/master/constants/syscalls.md)
- [x86 Linux の 32bit と 64bit のシステムコールの違い](https://www.mztn.org/lxasm64/x86_x64_table.html)

- [Cとアセンブラを組み合わせてコンパイルする](https://kobapan.hatenadiary.org/entry/20090524/1258476318)
- [6-8 演習: 画面に "Hi" と表示しよう](https://github.com/dilmnqvovpnmlib/BinaryAnalysisBook/tree/main/s6)
