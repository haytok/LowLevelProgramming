#!/bin/sh
stty -echo # 標準入力からの値を表示しないように設定
echo 'Type something: \c'
read STR
stty echo # 標準入力からの値を表示するように設定。
# stty echo をコメントアウトして、このシェルスクリプトを実行すると、標準入力が表示されない。
# つまり、キーボードを押下しても端末には入力文字列が表示されないが、命令は送っている状況になる。
# したがって stty echo を実行する必要がある。
echo '\nYou typed:' $STR
