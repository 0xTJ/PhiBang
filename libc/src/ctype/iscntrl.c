#include <ctype.h>

int iscntrl(int c) {
    if (c == EOF)
        return 0;
    else
        return (unsigned char)c <= 037 || (unsigned char)c == 0177;
}
