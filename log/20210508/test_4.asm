bits 32

global hello

hello:
  mov edx, [esp+4]
  add edx, 0x1
  mov eax, edx
  ret
