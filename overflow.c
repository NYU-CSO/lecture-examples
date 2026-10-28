/* overflow.c -- a minimal stack buffer overflow.
 *
 * vulnerable() copies its argument into a 16-byte stack buffer with no
 * bounds check.  Hand it a string longer than the buffer and strcpy keeps
 * writing past the end of buf, clobbering whatever sits above it on the
 * stack -- including vulnerable()'s own saved return address.
 *
 * Try it:
 *   ./overflow hello
 *       -> fits in buf; prints the string and returns normally.
 *   ./overflow AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA        (36 A's)
 *       -> overruns buf, smashes the saved return address, and the program
 *          crashes with a segfault when vulnerable() tries to return.
 *          Notice "vulnerable() returned normally" never prints.
 *
 * The Makefile builds this twice:
 *   overflow            -fno-stack-protector  -> the segfault above
 *   overflow-protected  -fstack-protector-all -> the canary catches the
 *                        smash and aborts with "stack smashing detected"
 *                        instead of jumping to the corrupted address.
 */
#include <stdio.h>
#include <string.h>

void vulnerable(const char *input)
{
    char buf[16];
    strcpy(buf, input);        /* the bug: no check that input fits in buf */
    printf("you entered: %s\n", buf);
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        printf("usage: %s <string>\n", argv[0]);
        return 1;
    }
    vulnerable(argv[1]);
    printf("vulnerable() returned normally\n");
    return 0;
}
