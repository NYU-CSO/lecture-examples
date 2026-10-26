#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/*
 * modern C headers no longer exports the unsafe gets() function, so we
 * declare it ourselves just to use it in this demo.  
 */
char *gets(char *s);

/*
 * get_input() reads a line from the user into an 8-byte buffer and checks
 * whether it equals the password.  gets() does NO bounds checking, so a line
 * longer than 8 bytes overflows buf and keeps writing up the stack, past
 * get_input()'s saved return address.  That is the vulnerability: by writing
 * the right bytes there, an attacker makes get_input() "return" to any code
 * they choose -- for example, straight into give_out_lots_of_money().
 */
bool
get_input()
{
    char buf[12];
    gets(buf);
    return strcmp(buf, "supersecret") == 0;
}

__attribute__((force_align_arg_pointer))
void
give_out_lots_of_money()
{
    printf("Congratulations! You have earned lots of $$$\n");
    exit(0);
}

int
main()
{
    if (get_input()) {
        give_out_lots_of_money();
    } else {
        printf("sorry dude, you don't have the right password\n");
    }
    return 0;
}
