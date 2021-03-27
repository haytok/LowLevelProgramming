# 11 章で学んだことや考えたことのログ

## この章で取り扱うライブラリ関数
- malloc
- calloc
- realloc
- free
- brk (2)

### マニュアル

- malloc

```bash
SYNOPSIS
       #include <stdlib.h>

       void *malloc(size_t size);

RETURN VALUE
       The  malloc() and calloc() functions return a pointer to the allocated memory, which is suitably aligned for any built-in type.  On error, these functions return
       NULL.  NULL may also be returned by a successful call to malloc() with a size of zero, or by a successful call to calloc() with nmemb or size equal to zero.
```

- calloc
- 第一引数に各要素のサイズを、第二引数には全体の大きさを入れる。

```bash
SYNOPSIS
       #include <stdlib.h>

       void *calloc(size_t nmemb, size_t size);

DESCRIPTION
       The  calloc()  function  allocates  memory for an array of nmemb elements of size bytes each and returns a pointer to the allocated memory.  The memory is set to
       zero.  If nmemb or size is 0, then calloc() returns either NULL, or a unique pointer value that can later be successfully passed to free().

RETURN VALUE
       The  malloc() and calloc() functions return a pointer to the allocated memory, which is suitably aligned for any built-in type.  On error, these functions return
       NULL.  NULL may also be returned by a successful call to malloc() with a size of zero, or by a successful call to calloc() with nmemb or size equal to zero.
```

- realloc

```bash
SYNOPSIS
       #include <stdlib.h>

       void *realloc(void *ptr, size_t size);

DESCRIPTION
       The realloc() function changes the size of the memory block pointed to by ptr to size bytes.  The contents will be unchanged in the range from the start  of  the
       region  up to the minimum of the old and new sizes.  If the new size is larger than the old size, the added memory will not be initialized.  If ptr is NULL, then
       the call is equivalent to malloc(size), for all values of size; if size is equal to zero, and ptr is not NULL, then the call is equivalent to free(ptr).   Unless
       ptr is NULL, it must have been returned by an earlier call to malloc(), calloc(), or realloc().  If the area pointed to was moved, a free(ptr) is done.

RETURN VALUE
       The  malloc() and calloc() functions return a pointer to the allocated memory, which is suitably aligned for any built-in type.  On error, these functions return
       NULL.  NULL may also be returned by a successful call to malloc() with a size of zero, or by a successful call to calloc() with nmemb or size equal to zero.
```

- free

```bash
SYNOPSIS
       #include <stdlib.h>

       void free(void *ptr);

DESCRIPTION
       The free() function frees the memory space pointed to by ptr, which must have been returned by a previous call to malloc(), calloc(), or  realloc().   Otherwise,
       or if free(ptr) has already been called before, undefined behavior occurs.  If ptr is NULL, no operation is performed.

RETURN VALUE
       The free() function returns no value.
```

- brk

```bash
```

## テスト方法

## この章の流れ

## 練習問題
### 11.4.1

```bash
このコマンドはtail.cと同じくリングバッファを使いますが、 動的にメモリを確保する必要があるため、mallocを使うところだけが違います。 
```

- fgetc の返り値に関して

```bash
RETURN VALUE
       fgetc(), getc() and getchar() return the character read as an unsigned char cast to an int or EOF on end of file or error.
```
