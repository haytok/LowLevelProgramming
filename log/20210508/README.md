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

- では、システムコール番号はどこで定義されているかと言うと、以下の順序でヘッダファイルを辿ると見つけることができる。

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

<!-- ### 
- 

#### 参考
- []()
- []()
- []() -->
