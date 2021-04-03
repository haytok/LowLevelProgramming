# 15 章で学んだことや考えたことのログ

## この章で取り扱うライブラリ関数
- va_start
- vfprintf
- fputc
- strchr
- strcpy
- toupper
- strncasecmp
- sprintf

## テスト方法
- `gcc -o httpd httpd.c && ./httpd .`

```bash
GET /index.html HTTP/1.1
Connection: close\r\n
Accept: */*\r\n
Host: i.lovesakura.net\r\n

```

## この章の流れ
- HTTP Server を C 言語で自作する。
