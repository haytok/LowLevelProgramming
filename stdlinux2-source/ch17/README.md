# 17 章で学んだことや考えたことのログ

## この章の流れ
- 自力のソケット接続

- デーモン化
- syslog を使ったロギング
- chroot を使ったセキュリティの向上
- それに伴うクレデンシャルの変更のサポート
- これらを全て指示するためのコマンドラインオプションの解析

## この章で取り扱うライブラリ関数
- daemon
- syslog
- openlog
- closelog
- vsyslog
- chroot

## テスト方法
- `gcc -o httpd httpd.c && ./httpd .`
- `http://localhost:8080/index.html` にアクセスする
