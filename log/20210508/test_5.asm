bits 32

global hello

hello:
  mov eax, 0x4
  mov ebx, 0x1
  mov ecx, [esp+4]
  mov edx, [esp+8]
  int 0x80
  add esp, 0x4
  ret
