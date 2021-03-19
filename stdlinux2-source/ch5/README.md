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

- `man stderr` の description について

```bash
SYNOPSIS
       #include <stdio.h>

       extern FILE *stdin;
       extern FILE *stdout;
       extern FILE *stderr;
```

- `man fprintf` について

```bash
SYNOPSIS
       #include <stdio.h>

       int printf(const char *format, ...);
       int fprintf(FILE *stream, const char *format, ...);
DESCRIPTION
    fprintf() and vfprintf() write output to the given output stream;
```

## ライブラリ
- fprintf
- perror

- open (man 2 open)
- read
- fopen

## Description
- perror (man 3 perror)

```bash
NAME
       perror - print a system error message

SYNOPSIS
       #include <stdio.h>

       void perror(const char *s);

DESCRIPTION
       The perror() function produces a message on standard error describing the last error encountered during a call to a system or library function.

       First  (if s is not NULL and *s is not a null byte ('\0')), the argument string s is printed, followed by a colon and a blank.  Then an error message correspond‐
       ing to the current value of errno and a new-line.

       When a system call fails, it usually returns -1 and sets the variable errno to a value describing what went wrong.  (These values can  be  found  in  <errno.h>.)
       Many  library  functions  do likewise.  The function perror() serves to translate this error code into human-readable form.
```
- open (man 2 open)

```bash
NAME
       open, openat, creat - open and possibly create a file

SYNOPSIS
       #include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>

       int open(const char *pathname, int flags);
       int open(const char *pathname, int flags, mode_t mode);

DESCRIPTION
       The  open() system call opens the file specified by pathname.  If the specified file does not exist, it may optionally (if O_CREAT is specified in flags) be cre‐
       ated by open().

RETURN VALUE
       open(), openat(), and creat() return the new file descriptor, or -1 if an error occurred (in which case, errno is set appropriately).
```
- read (man 2 read)
- 読み込んだ文字列数を返す。

```bash
NAME
       read - read from a file descriptor

SYNOPSIS
       #include <unistd.h>

       ssize_t read(int fd, void *buf, size_t count);

DESCRIPTION
       read() attempts to read up to count bytes from file descriptor fd into the buffer starting at buf.

RETURN VALUE
       On success, the number of bytes read is returned (zero indicates end of file), and the file position is advanced by this number.  It is not an error if this num‐
       ber is smaller than the number of bytes requested; this may happen for example because fewer bytes are actually available right now (maybe because we were  close
       to end-of-file, or because we are reading from a pipe, or from a terminal), or because read() was interrupted by a signal.  See also NOTES.

       On error, -1 is returned, and errno is set appropriately.  In this case, it is left unspecified whether the file position (if any) changes.
```

- char と unsignend char の違いについて

```text
どちらもサイズは1バイトですが
大きな違いは
char型　保存できる値は -127 ~ 127
unsigned char型　保存できる値は 0 - 255 です
```

- write (man 2 write)

```bash
NAME
       write - write to a file descriptor

SYNOPSIS
       #include <unistd.h>

       ssize_t write(int fd, const void *buf, size_t count);
```

- close (man 2 close)

```bash
NAME
       close - close a file descriptor

SYNOPSIS
       #include <unistd.h>

       int close(int fd);

DESCRIPTION
       close()  closes a file descriptor, so that it no longer refers to any file and may be reused.  Any record locks (see fcntl(2)) held on the file it was associated
       with, and owned by the process, are removed (regardless of the file descriptor that was used to obtain the lock).

RETURN VALUE
       close() returns zero on success.  On error, -1 is returned, and errno is set appropriately.
```

## その他のシステムコール

- lseek
- dup
- dup2
- ioctl
- fcntl

- lseek (man 2 lseek)

```bash
DESCRIPTION
       lseek()  repositions the file offset of the open file description associated with the file descriptor fd to the argument offset according to the directive whence
       as follows:

       SEEK_SET
              The file offset is set to offset bytes.

       SEEK_CUR
              The file offset is set to its current location plus offset bytes.

       SEEK_END
              The file offset is set to the size of the file plus offset bytes.
```

- dup, dup2 (man 2 dup)

```bash
DESCRIPTION
       The dup() system call creates a copy of the file descriptor oldfd, using the lowest-numbered unused file descriptor for the new descriptor.
```

- ioctl (man 2 ioctl)

```bash
DESCRIPTION
       The  ioctl() system call manipulates the underlying device parameters of special files.  In particular, many operating characteristics of character special files
       (e.g., terminals) may be controlled with ioctl() requests.  The argument fd must be an open file descriptor.
```

- fcntl (man 2 fcntl)

```bash
DESCRIPTION
       fcntl() performs one of the operations described below on the open file descriptor fd.  The operation is determined by cmd.
```
