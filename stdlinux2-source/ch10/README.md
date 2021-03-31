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
- マニュアルの後続に EXAMPLE がある。

```bash
SYNOPSIS
       #include <sys/types.h>
       #include <sys/stat.h>
       #include <unistd.h>

       int stat(const char *pathname, struct stat *statbuf);
       int lstat(const char *pathname, struct stat *statbuf);

DESCRIPTION
       These functions return information about a file, in the buffer pointed to by statbuf.  No permissions are required on the file itself, but—in the case of stat(),
       fstatat(), and lstat()—execute (search) permission is required on all of the directories in pathname that lead to the file.

       stat() and fstatat() retrieve information about the file pointed to by pathname; the differences for fstatat() are described below.

       lstat() is identical to stat(), except that if pathname is a symbolic link, then it returns information about the link itself, not the file that it refers to.

       fstat() is identical to stat(), except that the file about which information is to be retrieved is specified by the file descriptor fd.

   The stat structure
       All of these system calls return a stat structure, which contains the following fields:

           struct stat {
               dev_t     st_dev;         /* ID of device containing file */
               ino_t     st_ino;         /* Inode number */
               mode_t    st_mode;        /* File type and mode */
               nlink_t   st_nlink;       /* Number of hard links */
               uid_t     st_uid;         /* User ID of owner */
               gid_t     st_gid;         /* Group ID of owner */
               dev_t     st_rdev;        /* Device ID (if special file) */
               off_t     st_size;        /* Total size, in bytes */
               blksize_t st_blksize;     /* Block size for filesystem I/O */
               blkcnt_t  st_blocks;      /* Number of 512B blocks allocated */

               /* Since Linux 2.6, the kernel supports nanosecond
                  precision for the following timestamp fields.
                  For the details before Linux 2.6, see NOTES. */

               struct timespec st_atim;  /* Time of last access */
               struct timespec st_mtim;  /* Time of last modification */
               struct timespec st_ctim;  /* Time of last status change */

           #define st_atime st_atim.tv_sec      /* Backward compatibility */
           #define st_mtime st_mtim.tv_sec
           #define st_ctime st_ctim.tv_sec
           };

RETURN VALUE
       On success, zero is returned.  On error, -1 is returned, and errno is set appropriately.

EXAMPLE
       The following program calls lstat() and displays selected fields in the returned stat structure.

       #include <sys/types.h>
       #include <sys/stat.h>
       #include <time.h>
       #include <stdio.h>
       #include <stdlib.h>
       #include <sys/sysmacros.h>

       int
       main(int argc, char *argv[])
       {
           struct stat sb;

           if (argc != 2) {
               fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
               exit(EXIT_FAILURE);
           }

           if (lstat(argv[1], &sb) == -1) {
               perror("lstat");
               exit(EXIT_FAILURE);
           }

           printf("ID of containing device:  [%lx,%lx]\n",
                (long) major(sb.st_dev), (long) minor(sb.st_dev));

           printf("File type:                ");

           switch (sb.st_mode & S_IFMT) {
           case S_IFBLK:  printf("block device\n");            break;
           case S_IFCHR:  printf("character device\n");        break;
           case S_IFDIR:  printf("directory\n");               break;
           case S_IFIFO:  printf("FIFO/pipe\n");               break;
           case S_IFLNK:  printf("symlink\n");                 break;
           case S_IFREG:  printf("regular file\n");            break;
           case S_IFSOCK: printf("socket\n");                  break;
           default:       printf("unknown?\n");                break;
           }

           printf("I-node number:            %ld\n", (long) sb.st_ino);
           printf("Mode:                     %lo (octal)\n",
                   (unsigned long) sb.st_mode);

           printf("Link count:               %ld\n", (long) sb.st_nlink);
           printf("Ownership:                UID=%ld   GID=%ld\n",
                   (long) sb.st_uid, (long) sb.st_gid);

           printf("Preferred I/O block size: %ld bytes\n",
                   (long) sb.st_blksize);
           printf("File size:                %lld bytes\n",
                   (long long) sb.st_size);
           printf("Blocks allocated:         %lld\n",
                   (long long) sb.st_blocks);

           printf("Last status change:       %s", ctime(&sb.st_ctime));
           printf("Last file access:         %s", ctime(&sb.st_atime));
           printf("Last file modification:   %s", ctime(&sb.st_mtime));

           exit(EXIT_SUCCESS);
```

- chmod (2)

```bash
SYNOPSIS
       #include <sys/stat.h>

       int chmod(const char *pathname, mode_t mode);

DESCRIPTION
       The  chmod()  and  fchmod()  system  calls change a files mode bits.  (The file mode consists of the file permission bits plus the set-user-ID, set-group-ID, and
       sticky bits.)  These system calls differ only in how the file is specified:

RETURN VALUE
       On success, zero is returned.  On error, -1 is returned, and errno is set appropriately.
```

- chown (2)

```bash
SYNOPSIS
       #include <unistd.h>

       int chown(const char *pathname, uid_t owner, gid_t group);

DESCRIPTION
       These system calls change the owner and group of a file.  The chown(), fchown(), and lchown() system calls differ only in how the file is specified:

       * chown() changes the ownership of the file specified by pathname, which is dereferenced if it is a symbolic link.

RETURN VALUE
       On success, zero is returned.  On error, -1 is returned, and errno is set appropriately.
```

- utime (2)

```bash
SYNOPSIS
       #include <sys/types.h>
       #include <utime.h>

       int utime(const char *filename, const struct utimbuf *times);

DESCRIPTION
       Note: modern applications may prefer to use the interfaces described in utimensat(2).

       The utime() system call changes the access and modification times of the inode specified by filename to the actime and modtime fields of times respectively.

RETURN VALUE
       On success, zero is returned.  On error, -1 is returned, and errno is set appropriately.
```

- strtol (3)

```bash
SYNOPSIS
       #include <stdlib.h>

       long int strtol(const char *nptr, char **endptr, int base);

       long long int strtoll(const char *nptr, char **endptr, int base);

   Feature Test Macro Requirements for glibc (see feature_test_macros(7)):

       strtoll():
           _ISOC99_SOURCE
               || /* Glibc versions <= 2.19: */ _SVID_SOURCE || _BSD_SOURCE

DESCRIPTION
       The  strtol() function converts the initial part of the string in nptr to a long integer value according to the given base, which must be between 2 and 36 inclu‐
       sive, or be the special value 0.

       The string may begin with an arbitrary amount of white space (as determined by isspace(3)) followed by a single optional '+' or '-' sign.  If base is zero or 16,
       the  string may then include a "0x" or "0X" prefix, and the number will be read in base 16; otherwise, a zero base is taken as 10 (decimal) unless the next char‐
       acter is '0', in which case it is taken as 8 (octal).

       The remainder of the string is converted to a long int value in the obvious manner, stopping at the first character which is not a valid digit in the given base.
       (In bases above 10, the letter 'A' in either uppercase or lowercase represents 10, 'B' represents 11, and so forth, with 'Z' representing 35.)

       If endptr is not NULL, strtol() stores the address of the first invalid character in *endptr.  If there were no digits at all, strtol() stores the original value
       of nptr in *endptr (and returns 0).  In particular, if *nptr is not '\0' but **endptr is '\0' on return, the entire string is valid.

       The strtoll() function works just like the strtol() function but returns a long long integer value.

RETURN VALUE
       The strtol() function returns the result of the conversion, unless the value would underflow or overflow.  If an underflow occurs, strtol() returns LONG_MIN.  If
       an  overflow  occurs,  strtol()  returns  LONG_MAX.  In both cases, errno is set to ERANGE.  Precisely the same holds for strtoll() (with LLONG_MIN and LLONG_MAX
       instead of LONG_MIN and LONG_MAX).
```

## テスト方法

## この章の流れ

## 練習問題
### 10.11.1
- セグメンテーションフォルトが生じた時にあ、gdb を使ってデバッグすると、問題点が分かって良かった。

### 10.11.2
- open 元のファイルを rename したり unlink したりしても、すでに接続されているストリームを使うと、ファイルの読み書きを継続できる、ストリームを使えばの話し。

### 10.11.3
