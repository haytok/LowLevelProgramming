# 6 章で学んだことや考えたことのログ

## この章で取り扱うライブラリ関数

### stdio
- [ ] fopen (関連 fdopen)
- [ ] fclose (関連 fflush)

### バイト単位の入出力
- [ ] fgetc (関連 fgets, getc, getchar, ungetc)
- [ ] getc
- [ ] getchar
- [ ] ungetc

- [ ] fputc (関連 fputs, putc, putchar, puts)
- [ ] putc
- [ ] putchar

### 文字列の入出力 (-> もしかして文末の c や s は char や string のことな気がする)
- [ ] fgets

- [ ] fputs
- [ ] puts

- [ ] printf (関連 fprintf)
- [ ] fprintf

- [ ] scanf

### 固定長の入出力 
- [ ] fread (関連 fwrite)
- [ ] fwrite

### ファイルオフセットの操作
- [ ] fseek (関連 ftell)
- [ ] ftell
- [ ] rewind

- [ ] fseeko (関連 ftello)
- [ ] ftello


### ファイルディスクリプタと FILE 型
- [ ] fdopen (関連 fopen)

- [ ] fileno (関連 clearerr, feof, ferror)

### バッファリングの操作
- [ ] fflush (関連 fclose)

- [ ] setvbuf

### EOF とエラー
- [ ] clearerr
- [ ] feof
- [ ] ferror

### man を読んでいく

- man 3 fopen と man 3 fdopen
- file open と file descriptor open

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

- fclose
- buffer を破棄するのの fflush が呼び出される。

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

- fflush
- fclose と関係している。
- バッファに格納されているデータを出力する。

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

#### read 系統のライブラリ関数

- fgetc

```bash
SYNOPSIS
       #include <stdio.h>

       int fgetc(FILE *stream);

DESCRIPTION
       fgetc() reads the next character from stream and returns it as an unsigned char cast to an
       int, or EOF on end of file or error.

RETURN VALUE
       fgetc(), getc() and getchar() return the character read as an unsigned char cast to an int
       or EOF on end of file or error.
```

- fgets

```bash
SYNOPSIS
       #include <stdio.h>

       char *fgets(char *s, int size, FILE *stream);

DESCRIPTION
       fgets()  reads  in  at most one less than size characters from stream and stores them into the buffer pointed to by s.  Reading stops after an EOF or a newline.   If  a  newline  is read,  it  is  stored into the buffer.  A terminating null byte ('\0') is stored after the last character in the buffer.

RETURN VALUE
       fgets() returns s on success, and NULL on error or when end of file occurs while no  char‐
       acters have been read.
```

- getc

```bash
SYNOPSIS
       #include <stdio.h>

       int getc(FILE *stream);

DESCRIPTION
       getc() is equivalent to fgetc() except that it may be implemented as a macro which  evaluates stream more than once.

RETURN VALUE
       fgetc(), getc() and getchar() return the character read as an unsigned char cast to an int or EOF on end of file or error.
```

- getchar

```bash
SYNOPSIS
       #include <stdio.h>

       int getchar(void);

DESCRIPTION
       getchar() is equivalent to getc(stdin).

RETURN VALUE
       fgetc(), getc() and getchar() return the character read as an unsigned char cast to an int or EOF on end of file or error.
```

- ungetc

```bash
SYNOPSIS
       #include <stdio.h>

       int ungetc(int c, FILE *stream);

DESCRIPTION
       ungetc() pushes c back to stream, cast to unsigned char, where it is available for  subsequent read operations. Pushed-back characters will be returned in reverse order; only one pushback is guaranteed.

RETURN VALUE
       ungetc() returns c on success, or EOF on error.
```

#### read 系統のライブラリ関数

- fputc

```bash
SYNOPSIS
       #include <stdio.h>

       int fputc(int c, FILE *stream);

DESCRIPTION
       fputc() writes the character c, cast to an unsigned char, to stream.

RETURN VALUE
       fputc(), putc() and putchar() return the character written as an unsigned char cast to an int or EOF on error.
```

- fputs

```bash
SYNOPSIS
       #include <stdio.h>

       int fputs(const char *s, FILE *stream);

DESCRIPTION
       fputs() writes the string s to stream, without its terminating null byte ('\0').

RETURN VALUE
       puts() and fputs() return a nonnegative number on success, or EOF on error.
```

- putc

```bash
SYNOPSIS
       #include <stdio.h>

       int putc(int c, FILE *stream);

DESCRIPTION
       putc() is equivalent to fputc() except that it may be implemented as a macro which evaluates stream more than once.

RETURN VALUE
       fputc(), putc() and putchar() return the character written as an unsigned char cast to an int or EOF on error.
```

- putchar

```bash
SYNOPSIS
       #include <stdio.h>

       int putchar(int c);

DESCRIPTION
       putchar(c) is equivalent to putc(c, stdout).

RETURN VALUE
       fputc(), putc() and putchar() return the character written as an unsigned char cast to an int or EOF on error.
```

- puts

```bash
SYNOPSIS
       #include <stdio.h>

       int puts(const char *s);

DESCRIPTION
       puts() writes the string s and a trailing newline to stdout.

RETURN VALUE
       puts() and fputs() return a nonnegative number on success, or EOF on error.
```

- printf

```bash
SYNOPSIS
       #include <stdio.h>

       int printf(const char *format, ...);

DESCRIPTION
       The  functions  in the printf() family produce output according to a format as described below.  The functions printf() and vprintf() write output to stdout, the standard output stream; fprintf() and vfprintf() write output to the given output stream; sprintf(), snprintf(), vsprintf() and vsnprintf() write to the  character string str.
```

- fprintf

```bash
SYNOPSIS
       #include <stdio.h>

       int fprintf(FILE *stream, const char *format, ...);

DESCRIPTION
       The  functions  in the printf() family produce output according to a format as described below.  The functions printf() and vprintf() write output to stdout, the standard output stream; fprintf() and vfprintf() write output to the given output stream; sprintf(), snprintf(), vsprintf() and vsnprintf() write to the  character string str.
```

- scanf

```bash
SYNOPSIS
       #include <stdio.h>

       int scanf(const char *format, ...);

DESCRIPTION
       The  scanf()  family  of  functions scans input according to format as described below.  This format may contain conversion specifications; the results from such
       conversions, if any, are stored in the locations pointed to by the pointer arguments that follow format.  Each pointer argument must be of a type that is  appro‐
       priate for the value returned by the corresponding conversion specification.

       If  the  number  of  conversion  specifications in format exceeds the number of pointer arguments, the results are undefined.  If the number of pointer arguments
       exceeds the number of conversion specifications, then the excess pointer arguments are evaluated, but are otherwise ignored.

       The scanf() function reads input from the standard input stream stdin, fscanf() reads input from the stream pointer stream, and sscanf() reads its input from the
       character string pointed to by str.

RETURN VALUE
       On  success,  these functions return the number of input items successfully matched and assigned; this can be fewer than provided for, or even zero, in the event
       of an early matching failure.

       The value EOF is returned if the end of input is reached before either the first successful conversion or a matching failure occurs.  EOF is also returned  if  a
       read error occurs, in which case the error indicator for the stream (see ferror(3)) is set, and errno is set to indicate the error.
```

- fread

```bash
SYNOPSIS
       #include <stdio.h>

       size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);

DESCRIPTION
       The function fread() reads nmemb items of data, each size bytes long, from the stream pointed to by stream, storing them at the location given by ptr.

RETURN VALUE
       On  success,  fread()  and  fwrite()  return the number of items read or written.  This number equals the number of bytes transferred only when size is 1.  If an
       error occurs, or the end of the file is reached, the return value is a short item count (or zero).
```

- fwrite

```bash
SYNOPSIS
       #include <stdio.h>

       size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);

DESCRIPTION
       The function fread() reads nmemb items of data, each size bytes long, from the stream pointed to by stream, storing them at the location given by ptr.

       The function fwrite() writes nmemb items of data, each size bytes long, to the stream pointed to by stream, obtaining them from the location given by ptr.

```

- fseek

```bash
SYNOPSIS
       #include <stdio.h>

       int fseek(FILE *stream, long offset, int whence);

DESCRIPTION
       The  fseek()  function  sets  the file position indicator for the stream pointed to by stream.  The new position, measured in bytes, is obtained by adding offset bytes to the position specified by whence.  If whence is set to SEEK_SET, SEEK_CUR, or SEEK_END, the offset is relative to the start of  the  file,  the  current position  indicator,  or  end-of-file,  respectively.   A  successful call to the fseek() function clears the end-of-file indicator for the stream and undoes any effects of the ungetc(3) function on the same stream.

       The ftell() function obtains the current value of the file position indicator for the stream pointed to by stream.

RETURN VALUE
       Upon successful completion, fgetpos(), fseek(), fsetpos() return 0, and ftell() returns the current offset. Otherwise, -1 is returned and errno is set to indicate the error.
```

- ftell

```bash
SYNOPSIS
       #include <stdio.h>

       long ftell(FILE *stream);

DESCRIPTION
       The ftell() function obtains the current value of the file position indicator for the stream pointed to by stream.

RETURN VALUE
       ftell() returns the current offset. Otherwise, -1 is returned and errno is set to indicate the error.
```

- rewind

```bash
SYNOPSIS
       #include <stdio.h>

       int fseek(FILE *stream, long offset, int whence);

       void rewind(FILE *stream);

DESCRIPTION
       The rewind() function sets the file position indicator for the stream pointed to by stream to the beginning of the file.  It is equivalent to:

              (void) fseek(stream, 0L, SEEK_SET)

       except that the error indicator for the stream is also cleared (see clearerr(3)).

RETURN VALUE
       The rewind() function returns no value.
```

- fseeko

```bash
SYNOPSIS
       #include <stdio.h>

       int fseeko(FILE *stream, off_t offset, int whence);

DESCRIPTION
       The  fseeko()  and  ftello()  functions  are identical to fseek(3) and ftell(3) (see fseek(3)), respectively, except that the offset argument of fseeko() and the
       return value of ftello() is of type off_t instead of long.

       On some architectures, both off_t and long are 32-bit types, but defining _FILE_OFFSET_BITS with the value 64 (before including any header files) will turn off_t
       into a 64-bit type.

RETURN VALUE
       On successful completion, fseeko() returns 0, while ftello() returns the current offset.  Otherwise, -1 is returned and errno is set to indicate the error.
```

- ftello

```bash
SYNOPSIS
       #include <stdio.h>

       off_t ftello(FILE *stream);

DESCRIPTION
       The  fseeko()  and  ftello()  functions  are identical to fseek(3) and ftell(3) (see fseek(3)), respectively, except that the offset argument of fseeko() and the
       return value of ftello() is of type off_t instead of long.

       On some architectures, both off_t and long are 32-bit types, but defining _FILE_OFFSET_BITS with the value 64 (before including any header files) will turn off_t
       into a 64-bit type.

RETURN VALUE
       On successful completion, fseeko() returns 0, while ftello() returns the current offset.  Otherwise, -1 is returned and errno is set to indicate the error.
```

- fileno

```bash
SYNOPSIS
       #include <stdio.h>

       int fileno(FILE *stream);

DESCRIPTION
       The function fileno() examines the argument stream and returns its integer file descriptor.

ERRORS
       These  functions should not fail and do not set the external variable errno.  (However, in case fileno() detects that its argument is not a valid stream, it must
       return -1 and set errno to EBADF.)
```

- clearerr

```bash
SYNOPSIS
       #include <stdio.h>

       void clearerr(FILE *stream);

DESCRIPTION
       The function clearerr() clears the end-of-file and error indicators for the stream pointed to by stream.

ERRORS
       These  functions should not fail and do not set the external variable errno.  (However, in case fileno() detects that its argument is not a valid stream, it must
       return -1 and set errno to EBADF.)
```

- feof

```bash
SYNOPSIS
       #include <stdio.h>

       int feof(FILE *stream);

DESCRIPTION
       The  function  feof()  tests  the  end-of-file  indicator  for the stream pointed to by stream, returning nonzero if it is set.  The end-of-file indicator can be
       cleared only by the function clearerr().

ERRORS
       These  functions should not fail and do not set the external variable errno.  (However, in case fileno() detects that its argument is not a valid stream, it must
       return -1 and set errno to EBADF.)
```

- ferror

```bash
SYNOPSIS
       #include <stdio.h>

       int ferror(FILE *stream);

DESCRIPTION
       The function ferror() tests the error indicator for the stream pointed to by stream, returning nonzero if it is set.  The error indicator can be  reset  only  by
       the clearerr() function.

ERRORS
       These  functions should not fail and do not set the external variable errno.  (However, in case fileno() detects that its argument is not a valid stream, it must
       return -1 and set errno to EBADF.)
```

- setvbuf

```bash
SYNOPSIS
       #include <stdio.h>

       int setvbuf(FILE *stream, char *buf, int mode, size_t size);

DESCRIPTION
       The three types of buffering available are unbuffered, block buffered, and line buffered.  When an output stream is unbuffered, information appears on the desti‐
       nation file or terminal as soon as written; when it is block buffered many characters are saved up and written as a block; when it is  line  buffered  characters
       are  saved  up until a newline is output or input is read from any stream attached to a terminal device (typically stdin).  The function fflush(3) may be used to
       force the block out early.  (See fclose(3).)

       Normally all files are block buffered.  If a stream refers to a terminal (as stdout normally does), it is line buffered.  The standard  error  stream  stderr  is
       always unbuffered by default.

       The setvbuf() function may be used on any open stream to change its buffer.  The mode argument must be one of the following three macros:

              _IONBF unbuffered

              _IOLBF line buffered

              _IOFBF fully buffered

       Except  for unbuffered files, the buf argument should point to a buffer at least size bytes long; this buffer will be used instead of the current buffer.  If the
       argument buf is NULL, only the mode is affected; a new buffer will be allocated on the next read or write operation.  The setvbuf() function  may  be  used  only
       after opening a stream and before any other operations have been performed on it.

       The other three calls are, in effect, simply aliases for calls to setvbuf().  The setbuf() function is exactly equivalent to the call

           setvbuf(stream, buf, buf ? _IOFBF : _IONBF, BUFSIZ);

       The  setbuffer()  function  is  the  same,  except that the size of the buffer is up to the caller, rather than being determined by the default BUFSIZ.  The set‐
       linebuf() function is exactly equivalent to the call:

           setvbuf(stream, NULL, _IOLBF, 0);

RETURN VALUE
       The function setvbuf() returns 0 on success.  It returns nonzero on failure (mode is invalid or the request cannot be honored).  It may set errno on failure.

       The other functions do not return a value.
```
