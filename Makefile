CFLAGS := -Werror -c -Og -g -std=gnu11 -fomit-frame-pointer -fno-stack-protector -fcf-protection=none

GCC = gcc

all : exampleoverflow

%.o : %.c
	$(GCC) $(CFLAGS) $*.c

exampleoverflow: exampleoverflow.o
	$(GCC) -no-pie $^ -o $@

clean :
	rm -f exampleoverflow exampleoverflow.o

