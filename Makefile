# Two builds of the same stack-overflow bug (overflow.c), to show what the
# stack protector does.
#
#   overflow            built WITHOUT the canary (-fno-stack-protector):
#                       a long argument smashes the saved return address and
#                       the program segfaults when vulnerable() returns.
#
#   overflow-protected  built WITH the canary (-fstack-protector-all):
#                       gcc places a guard ("canary") value between buf and
#                       the saved return address; the function checks it on
#                       the way out, detects the smash, prints
#                       "*** stack smashing detected ***" and aborts before
#                       the corrupted return address is ever used.
#
# -U_FORTIFY_SOURCE turns off glibc's fortified strcpy so that the *stack
# protector* is the only thing catching the overflow -- otherwise the
# fortified strcpy could trip first and muddy the lesson.

CC      = gcc
CFLAGS := -Og -g -std=gnu11 -U_FORTIFY_SOURCE

all: overflow overflow-protected

overflow: overflow.c
	$(CC) $(CFLAGS) -fno-stack-protector -o $@ $<

overflow-protected: overflow.c
	$(CC) $(CFLAGS) -fstack-protector-all -o $@ $<

clean:
	rm -f overflow overflow-protected

.PHONY: all clean
