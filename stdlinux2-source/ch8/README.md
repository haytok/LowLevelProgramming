# 8 章で学んだことや考えたことのログ

## この章で取り扱うライブラリ関数
- regcomp
- regfree
- regexec
- regerror

### マニュアル

- regcomp (man 3 regcomp)

```bash
SYNOPSIS
       #include <sys/types.h>
       #include <regex.h>

       int regcomp(regex_t *preg, const char *regex, int cflags);

DESCRIPTION
   POSIX regex compiling
       regcomp()  is used to compile a regular expression into a form that is suit‐
       able for subsequent regexec() searches.

       regcomp() is supplied with preg, a pointer to a pattern buffer storage area;
       regex,  a  pointer  to  the null-terminated string and cflags, flags used to
       determine the type of compilation.

RETURN VALUE
       regcomp()  returns  zero  for  a successful compilation or an error code for
       failure.
```

- regfree

```bash
SYNOPSIS
       void regfree(regex_t *preg);

DESCRIPTION
       Supplying regfree() with a precompiled pattern buffer, preg  will  free  the
       memory allocated to the pattern buffer by the compiling process, regcomp().
```

- regexec

```bash
SYNOPSIS
       int regexec(const regex_t *preg, const char *string, size_t nmatch,
                   regmatch_t pmatch[], int eflags);

DESCRIPTION
   POSIX regex matching
       regexec() is used to match a null-terminated string against the  precompiled
       pattern  buffer,  preg.   nmatch  and pmatch are used to provide information
       regarding the location of any matches.  eflags may be the bitwise-or of  one
       or  both of REG_NOTBOL and REG_NOTEOL which cause changes in matching behav‐
       ior described below.

RETURN VALUE
       regexec() returns zero for a successful match or REG_NOMATCH for failure.
```

- regerror

```bash
SYNOPSIS
       void regfree(regex_t *preg);

DESCRIPTION
       regerror()  is  passed  the error code, errcode, the pattern buffer, preg, a
       pointer to a character string buffer, errbuf, and the  size  of  the  string
       buffer,  errbuf_size.  It returns the size of the errbuf required to contain
       the null-terminated error message string.  If both  errbuf  and  errbuf_size
       are  nonzero,  errbuf is filled in with the first errbuf_size - 1 characters
       of the error message and a terminating null byte ('\0').
```

## テスト方法
- `gcc -o grep grep.c && cat grep.c | ./grep argc`
- `gcc -o grep grep.c | ./grep argc grep.c`

## この章の流れ

## 練習問題
### 8.3.1

### 8.3.2
