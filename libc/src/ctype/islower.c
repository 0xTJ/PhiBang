#include <ctype.h>

int islower(int c) {
    if (c == EOF)
        return 0;
    else
        return 'a' <= (unsigned char)c && (unsigned char)c <= 'z';
}
