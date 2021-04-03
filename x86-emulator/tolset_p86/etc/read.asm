    jmp near entry
    nop
    dw 512
    db 4
    dw 4
    db 2
    dw 512
    dw 0
    db 248
    dw 250
    dw 63
    dw 255
    dd 0
    dd 256000
    db 128
    db 0
    db 41
    dd 2963790959
    db "NO NAME    "
    db "FAT16   "
    times 0x3e - ($ - $$) db 0
entry:
    xor cx,cx
    mov ss,cx
