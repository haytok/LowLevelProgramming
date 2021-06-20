global main

main:
  push 0x0a216948
  mov eax, 0x4
  mov ebx, 0x1
  mov ecx, esp
  mov edx, 0x4
  int 0x80
  add esp, 0x4
