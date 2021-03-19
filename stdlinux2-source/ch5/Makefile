CFLAGS=-std=c11 -g
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)

cat: $(OBJS)
		$(CC) -o cat cat.c $(LDFLAGS)

test: cat
		./cat input.txt input1.txt input2.txt

clean:
		rm -f k8cc *.o *~ tmp*

.PHONY: test clean
