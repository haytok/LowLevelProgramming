TARGET = casm-c-sample.bin
Z_TOOLS = ../z_tools

CC = gcc
LD = ld
CFLAGS += -nostdlib -fno-asynchronous-unwind-tables \
	-I$(Z_TOOLS)/i386-elf-gcc/include -g -fno-stack-protector
LDFLAGS += --entry=func --oformat=binary

.PHONY: all
all :
	make $(TARGET)

%.o : %.c Makefile
	$(CC) $(CFLAGS) -c $<

%.bin : %.o Makefile
	$(LD) $(LDFLAGS) -o $@ $<
