# Deliberately-vulnerable demo.  The flags turn off the protections that
# would otherwise stop a classic stack-smash, so students can see the
# hijack work:
#   -fno-stack-protector   no stack canary
#   -no-pie                fixed load address, so function addresses are known
#   -fcf-protection=none   no CET/shadow-stack (which blocks return hijacks)
CFLAGS := -c -Og -g -std=gnu11 -fomit-frame-pointer -fno-stack-protector -fcf-protection=none

GCC = gcc

all : exampleoverflow

%.o : %.c
	$(GCC) $(CFLAGS) $*.c

exampleoverflow: exampleoverflow.o
	$(GCC) -no-pie $^ -o $@

clean :
	rm -f exampleoverflow exampleoverflow.o
