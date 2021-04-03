BITS 16
	org 0x7c00

start:
	mov ax, 0
	mov ss, ax
	mov sp, 0x7c00
	mov ds, ax
	mov es, ax
	mov si, msg
	call puts
fin:
	hlt
	jmp fin

puts:
	mov al, [si]
        inc si
	cmp al, 0
	je puts_fin
	mov ah, 0x0e
	mov bx, 15
	int 0x10
	jmp puts
puts_fin:
	ret

msg:
	db "Hello, world!!", 0x0d, 0x0a, 0

	times 0x1fe - ($ - $$) db 0
	db 0x55, 0xaa
