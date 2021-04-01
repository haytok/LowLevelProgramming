# 14 章で学んだことや考えたことのログ

## この章で取り扱うライブラリ関数
- getcwd
- chdir
- environ (man 7 environ)
- getenv
- putenv
- getpwuid
- getpwnam
- getgrgid
- getgrnam
- getrusage
- time
- gettimeofday
- localtime
- gmtime
- mktime
- asctme
- ctime
- strftime

### マニュアル

- 

```bash
```

## テスト方法

## この章の流れ

## 練習問題
### 14.8.1
- プロセスのカレントディレクトリは親プロセスから引き継がれるので、子プロセスであれば、その情報を引き継ぐことができるからである。

### 14.8.2
- 自分自身以外のプロセスの属性を変更することができないからである。cd コマンドがシェルから分離されていると、変更できるのは cd プロセスのカレントディレクトリだけで、シェルプロセスのカレントディレクトリは変更できない。

### 14.8.3
- 
