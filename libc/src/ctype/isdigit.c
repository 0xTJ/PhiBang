#include <ctype.h>

int isdigit(int c) {
    if (c == EOF)
        return 0;
    else
        return '0' <= (unsigned char)c && (unsigned char)c <= '9';
}
