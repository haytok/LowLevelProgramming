mov eax, 0
mov ecx, eax
jmp loop_end
loop:
add eax, ecx
inc ecx
loop_end:
cmp ecx, 10
jl loop
