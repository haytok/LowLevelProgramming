# 8 章で学んだことや考えたことのログ

## この章で取り扱うライブラリ関数
- opendir
- readdir
- closedir

- mkdir (2)
- umask (2)

- rmdir (2)

- link (2)

- symlink (2)
- readlink (2)

- unlink (2)

- rename (2)

- stat (2)

- chmod (2)
- chown (2)
- utime (2)

### マニュアル

- opendir

```bash
SYNOPSIS
       #include <sys/types.h>
       #include <dirent.h>

       DIR *opendir(const char *name);

DESCRIPTION
       The  opendir() function opens a directory stream corresponding to the directory name, and returns a pointer to the directory stream.  The stream is positioned at the first entry in the directory.

RETURN VALUE
       The opendir() and fdopendir() functions return a pointer to the directory stream.  On error, NULL is returned, and errno is set appropriately.
```

- readdir

```bash
SYNOPSIS
       #include <dirent.h>

       struct dirent *readdir(DIR *dirp);

DESCRIPTION
       The readdir() function returns a pointer to a dirent structure representing the next directory entry in the directory stream pointed to by dirp.  It returns NULL
       on reaching the end of the directory stream or if an error occurred.

       In the glibc implementation, the dirent structure is defined as follows:

           struct dirent {
               ino_t          d_ino;       /* Inode number */
               off_t          d_off;       /* Not an offset; see below */
               unsigned short d_reclen;    /* Length of this record */
               unsigned char  d_type;      /* Type of file; not supported
                                              by all filesystem types */
               char           d_name[256]; /* Null-terminated filename */
           };

RETURN VALUE
       On success, readdir() returns a pointer to a dirent structure.  (This structure may be statically allocated; do not attempt to free(3) it.)

       If the end of the directory stream is reached, NULL is returned and errno is not changed.  If an error occurs, NULL is returned and errno is  set  appropriately.
       To distinguish end of stream and from an error, set errno to zero before calling readdir() and then check the value of errno if NULL is returned.
```

- closedir

```bash
SYNOPSIS
       #include <sys/types.h>

       #include <dirent.h>

       int closedir(DIR *dirp);

DESCRIPTION
       The  closedir() function closes the directory stream associated with dirp.  A successful call to closedir() also closes the underlying file descriptor associated
       with dirp.  The directory stream descriptor dirp is not available after this call.

RETURN VALUE
       The closedir() function returns 0 on success.  On error, -1 is returned, and errno is set appropriately.
```

- mkdir (2)

```bash
SYNOPSIS
       #include <sys/stat.h>
       #include <sys/types.h>

       int mkdir(const char *pathname, mode_t mode);

RETURN VALUE
       mkdir() and mkdirat() return zero on success, or -1 if an error occurred (in which case, errno is set appropriately).
```

- umask (2)

```bash
SYNOPSIS
       #include <sys/types.h>
       #include <sys/stat.h>

       mode_t umask(mode_t mask);

DESCRIPTION
       umask()  sets the calling processs file mode creation mask (umask) to mask & 0777 (i.e., only the file permission bits of mask are used), and returns the previ‐
       ous value of the mask.

       The umask is used by open(2), mkdir(2), and other system calls that create files to modify the permissions placed on newly created files or directories.  Specif‐
       ically, permissions in the umask are turned off from the mode argument to open(2) and mkdir(2).

RETURN VALUE
       This system call always succeeds and the previous value of the mask is returned.
```

- rmdir (2)

```bash
SYNOPSIS
       #include <unistd.h>

       int rmdir(const char *pathname);

DESCRIPTION
       rmdir() deletes a directory, which must be empty.

RETURN VALUE
       On success, zero is returned.  On error, -1 is returned, and errno is set appropriately.
```

- link (2)

```bash
SYNOPSIS
       #include <unistd.h>

       int link(const char *oldpath, const char *newpath);

DESCRIPTION
       link() creates a new link (also known as a hard link) to an existing file.

       If newpath exists, it will not be overwritten.

RETURN VALUE
       On success, zero is returned.  On error, -1 is returned, and errno is set appropriately.
```

- symlink (2)

```bash
SYNOPSIS
       #include <unistd.h>

       int symlink(const char *target, const char *linkpath);

DESCRIPTION
       symlink() creates a symbolic link named linkpath which contains the string target.

RETURN VALUE
       On success, zero is returned.  On error, -1 is returned, and errno is set appropriately.
```

- readlink (2)

```bash
SYNOPSIS
       #include <unistd.h>

       ssize_t readlink(const char *pathname, char *buf, size_t bufsiz);

DESCRIPTION
       readlink()  places  the contents of the symbolic link pathname in the buffer buf, which has size bufsiz.  readlink() does not append a null byte to buf.  It will
       (silently) truncate the contents (to a length of bufsiz characters), in case the buffer is too small to hold all of the contents.

RETURN VALUE
       On  success,  these  calls  return the number of bytes placed in buf.  (If the returned value equals bufsiz, then truncation may have occurred.)  On error, -1 is
       returned and errno is set to indicate the error.
```

- unlink (2)

```bash
SYNOPSIS
       #include <unistd.h>

       int unlink(const char *pathname);

DESCRIPTION
       unlink()  deletes a name from the filesystem.  If that name was the last link to a file and no processes have the file open, the file is deleted and the space it
       was using is made available for reuse.

RETURN VALUE
       On success, zero is returned.  On error, -1 is returned, and errno is set appropriately.
```

- rename (2)

```bash
SYNOPSIS
       #include <stdio.h>

       int rename(const char *oldpath, const char *newpath);

DESCRIPTION
       rename()  renames  a  file,  moving  it  between directories if required.  Any other hard links to the file (as created using link(2)) are unaffected.  Open file
       descriptors for oldpath are also unaffected.

RETURN VALUE
       On success, zero is returned.  On error, -1 is returned, and errno is set appropriately.
```

- stat (2)

```bash
```

- chmod (2)

```bash
```

- chown (2)

```bash
```

- utime (2)

```bash
```

## テスト方法

## この章の流れ

## 練習問題
### 10.11.1

### 10.11.2

### 10.11.3
