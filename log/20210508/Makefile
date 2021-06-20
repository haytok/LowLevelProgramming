test_3: test_3.c
	nasm -f elf64 -o syscall_test_3.o test_3.asm
	gcc -c test_3.c
	gcc -o test_3.out test_3.o syscall_test_3.o
	./test_3.out

test_4: test_4.c
	nasm -f elf32 -o syscall_test_4.o test_4.asm
	gcc -m32 -o test_4.o -c test_4.c
	gcc -m32 -o test_4.out test_4.o syscall_test_4.o

test_5: test_5.c
	nasm -f elf32 -o syscall_test_5.o test_5.asm
	gcc -m32 -o test_5.o -c test_5.c
	gcc -m32 -o test_5.out test_5.o syscall_test_5.o
	./test_5.out

test_8: test_8.c
	nasm -f elf32 -o syscall_test_8.o test_8.asm
	gcc -m32 -o test_8.o -c test_8.c
	gcc -m32 -o test_8.out test_8.o syscall_test_8.o
	./test_8.out

.PHONY: clean
clean:
	rm -rf *.out
