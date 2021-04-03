TARGET = px86
OBJS = instruction.o modrm.o emulator_function.o io.o

CFLAGS = -Wall
DEL = rm

all:
	make $(TARGET)

$(TARGET): $(OBJS) main.o Makefile int
	$(CC) -o $(TARGET) $(OBJS) main.o

test: $(OBJS) test.o Makefile int
	$(CC) -o test $(OBJS) test.o

int: int.asm
	nasm int.asm

.PHONY: clean
clean:
	$(DEL) $(OBJS)
