# 6 章で学んだことや考えたことのログ

## この章で取り扱うライブラリ関数

### stdio
- [] fopen
- [] fclose

### バイト単位の入出力
- [] fgetc
- [ ] fputc
- [ ] getc
- [ ] putc
- [ ] getchar
- [ ] putchar
- [ ] ungetc

### 文字列の入出力 (-> もしかして文末の c や s は char や string のことな気がする)
- [ ] fgets
- [ ] fputs
- [ ] puts
- [ ] printf
- [ ] fprintf
- [ ] scanf

### 固定長の入出力 
- [ ] fread
- [ ] fwrite

### ファイルオフセットの操作
- [ ] fseek
- [ ] fseeko
- [ ] ftell
- [ ] ftello
- [ ] rewind

### ファイルディスクリプタと FILE 型
- [ ] fileno
- [ ] fdopen

### バッファリングの操作
- [ ] fflush
- [ ] setvbuf

### EOF とエラー
- [ ] feof
- [ ] ferror
- [ ] clearerr

### man を読んでいく

- man 3 fopen と man 3 fdopen (file open と file descriptor open)

```bash
SYNOPSIS
       #include <stdio.h>

       FILE *fopen(const char *pathname, const char *mode);

       FILE *fdopen(int fd, const char *mode);

DESCRIPTION
       The fopen() function opens the file whose name is the string pointed to by pathname and associates a stream with it.

       The fdopen() function associates a stream with the existing file descriptor, fd.  The mode of the stream (one of the values "r", "r+", "w", "w+", "a", "a+") must
       be  compatible with the mode of the file descriptor.  The file position indicator of the new stream is set to that belonging to fd, and the error and end-of-file
       indicators are cleared.  Modes "w" or "w+" do not cause truncation of the file.  The file descriptor is not dup ed, and will be closed when the stream created by dopen() is closed.  The result of applying fdopen() to a shared memory object is undefined.

RETURN VALUE
       Upon successful completion fopen(), fdopen() and freopen() return a FILE pointer.  Otherwise, NULL is returned and errno is set to indicate the error.
```

- fclose (buffer を破棄するのの fflush が呼び出される。)

```bash
SYNOPSIS
       #include <stdio.h>

       int fclose(FILE *stream);

DESCRIPTION
       The fclose() function flushes the stream pointed to by stream (writing any buffered output data using fflush(3)) and closes the underlying file descriptor.

       The behaviour of fclose() is undefined if the stream parameter is an illegal pointer, or is a descriptor already passed to a previous invocation of fclose().

RETURN VALUE
       Upon  successful  completion,  0  is returned.  Otherwise, EOF is returned and errno is set to indicate the error.  In either case, any further access (including
       another call to fclose()) to the stream results in undefined behavior.
```

- fflush (fclose を関係している)
- バッファに格納されているデータを出力します。

```bash
SYNOPSIS
       #include <stdio.h>

       int fflush(FILE *stream);

DESCRIPTION
       For output streams, fflush() forces a write of all user-space buffered data for the given output or update stream via the streams underlying write function.

       For  input  streams associated with seekable files (e.g., disk files, but not pipes or terminals), fflush() discards any buffered data that has been fetched from
       the underlying file, but has not been consumed by the application.

RETURN VALUE
       Upon successful completion 0 is returned.  Otherwise, EOF is returned and errno is set to indicate the error.
```

- 

```bash
```

- 

```bash
```

- 

```bash
```

- 

```bash
```

- 

```bash
```

- 

```bash
```

- 

```bash
```

- 

```bash
```

- 

```bash
```

- 

```bash
```

- 

```bash
```

- 

```bash
```

- 

```bash
```

- 

```bash
```

- 

```bash
```

- 

```bash
```
