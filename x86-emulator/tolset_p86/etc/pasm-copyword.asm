mov eax, [0x7c00]
mov [0x7a00], eax

;こんな書き方もできる。
mov ebx, 0x7a00
mov eax, [ebx+0x200]
mov [ebx], eax
